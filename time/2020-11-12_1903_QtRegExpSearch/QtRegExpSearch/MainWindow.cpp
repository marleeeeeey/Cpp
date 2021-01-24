#include <QFileDialog>
#include <QDirIterator>
#include <algorithm>
#include <functional>
#include <QMessageBox>
#include <QTextStream>
#include <QSettings>
#include <QInputDialog>
#include <QLabel>
#include <QDebug>
#include <QProcess>
#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "MyHelper.hpp"

using namespace MyHelper;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pStatusBarLabel = new QLabel(this);
    ui->statusBar->addWidget(m_pStatusBarLabel);

    QObject::connect(ui->buttonRootPathBrowse, SIGNAL(clicked()),
                     this, SLOT(slotBrowseRootDirectory()));

    QObject::connect(ui->buttonFindFiles, SIGNAL(clicked()),
                     this, SLOT(slotStartFileSearch()));

    QObject::connect(ui->buttonFindLines, SIGNAL(clicked()),
                     this, SLOT(slotStartLineSearch()));

    QObject::connect(ui->buttonComplexFind, SIGNAL(clicked()),
                     this, SLOT(slotComplexFind()));

    QObject::connect(ui->buttonStop, SIGNAL(clicked()),
                     this, SLOT(slotStopSearch()));

    QObject::connect(ui->buttonPresetSave, SIGNAL(clicked()),
                     this, SLOT(slotSavePreset()));

    QObject::connect(ui->buttonPresetSaveAs, SIGNAL(clicked()),
                     this, SLOT(slotSaveAsPreset()));

    QObject::connect(ui->buttonPresetLoad, SIGNAL(clicked()),
                     this, SLOT(slotLoadActivePreset()));

    QObject::connect(ui->listWidgetPresets, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                     this, SLOT(slotLoadPreset(QListWidgetItem*)));

    QObject::connect(ui->buttonPresetRemove, SIGNAL(clicked()),
                     this, SLOT(slotRemoveActivePreset()));

    QObject::connect(ui->checkBoxUseFileListAsSource, SIGNAL(stateChanged(int)),
                     this, SLOT(slotFileListAsSourceStateChanged(int)));

    QObject::connect(ui->checkBoxIgnoreMaskActive, SIGNAL(stateChanged(int)),
                     this, SLOT(slotShowIgnoreFiltersStateChanged(int)));

    QObject::connect(ui->textEditFileList, SIGNAL(selectionChanged()),
                     this, SLOT(slotOnSelectionChanged()));

    QObject::connect(ui->textEditLineList, SIGNAL(selectionChanged()),
                     this, SLOT(slotOnSelectionChanged()));

    QObject::connect(ui->textEditResultFileList, SIGNAL(selectionChanged()),
                     this, SLOT(slotOnSelectionChanged()));

    QObject::connect(ui->pushButtonOpenSelectedFiles, SIGNAL(clicked()),
                     this, SLOT(slotTryOpenSelectedFiles()));

    QObject::connect(ui->pushButtonBrowseExternalFileViewer, SIGNAL(clicked()),
                     this, SLOT(slotBrowseExternalFileViewer()));

    QObject::connect(ui->checkBoxWordWrapEnabled, SIGNAL(stateChanged(int)),
                     this, SLOT(slotWordWrapStateChanged(int)));


    m_pSettings = new QSettings(this);
    m_defaultPresetName = "DefaultPreset";
    m_presetsGroup = "Presets";
    m_appSettingsGroup = "ApplicationSettings";
    readApplicationSharedSettings();
    readPresetSettings(m_defaultPresetName);

    QFont font = ui->textEditLineList->font();
    font.setFamily("Courier New");
    font.setStyleHint(QFont::Monospace);
    ui->textEditLineList->setFont(font);
}

MainWindow::~MainWindow()
{
    writeApplicationSharedSettings();
    writePresetSettings(m_defaultPresetName);
    delete ui;
}

void MainWindow::handleError(QString msg)
{
    QMessageBox::warning(this, "Warning", msg);
}

void MainWindow::startSearchInDirectory(QString dirStr, QRegExp fileRegExp, QRegExp fileIgnoreRegExp)
{
    ui->textEditFileList->clear();
    QDirIterator dirIterator(dirStr, QDirIterator::Subdirectories);
    int scanFileNumber = 0;
    int foundFileNumber = 0;
    int ignoredFileNumber = 0;
    while (dirIterator.hasNext())
    {
        QApplication::processEvents();
        if(m_stopSearchFlag == true)
        {
            break;
        }
        QString filePath = QDir::toNativeSeparators(dirIterator.next());
        QFileInfo fileInfo(filePath);
        if(fileInfo.isFile())
        {

            auto filePathMatch = getFilePathMatch(filePath, fileRegExp, fileIgnoreRegExp);
            switch(filePathMatch)
            {
            case FileMatch::Matched:
                onFileFound(filePath);
                foundFileNumber++;
                break;
            case FileMatch::Ignored:
                ignoredFileNumber++;
            case FileMatch::NotMatched:
            default:
                break;
            }

            scanFileNumber++;

            QString statusBarMessage;
            QTextStream out(&statusBarMessage);
            out << "File search. Scanned: " << scanFileNumber << "; Found: " << foundFileNumber
                << "; Ignored: " << ignoredFileNumber;
            m_pStatusBarLabel->setText(statusBarMessage);
        }
    }
}

void MainWindow::onFileFound(QString filePath)
{
    ui->textEditFileList->append(filePath);
}

void MainWindow::setSearchActiveStatus(bool b)
{
    ui->buttonFindFiles->setEnabled(!b);
    ui->buttonFindLines->setEnabled(!b);
    ui->buttonComplexFind->setEnabled(!b);
    ui->buttonStop->setEnabled(b);

    if(b == true)
    {
        m_stopSearchFlag = false;
    }
}

void MainWindow::slotBrowseRootDirectory()
{
    QString dir = QFileDialog
            ::getExistingDirectory(this,
                                   tr("Open Directory"),
                                   QCoreApplication::applicationDirPath(),
                                   QFileDialog::ShowDirsOnly
                                   | QFileDialog::DontResolveSymlinks);
    dir = QDir::toNativeSeparators(dir);
    if(!dir.isEmpty())
    {
        ui->lineEditRootPath->setText(dir);
    }
}

void MainWindow::slotStartFileSearch()
{
    if(isFileListAsSourceFlagActive())
    {
        searchFilesInFileList();
    }
    else
    {
        searchFilesInDirectory();
    }
}

void MainWindow::slotStartLineSearch()
{
    QStringList fileList = getFileList();
    if(fileList.isEmpty())
    {
        handleError("File list is empty");
        return;
    }

    QRegExp lineRegExp = getLineRegExp();

    if(lineRegExp.isEmpty())
    {
        handleError(QString("Line reg exp is empty"));
        return;
    }

    if(!lineRegExp.isValid())
    {
        handleError(QString("Line reg exp is not valid: %1")
                    .arg(lineRegExp.errorString()));
        return;
    }

    setSearchActiveStatus(true);
    setFileAndLineTabActive();

    if(!ui->checkBoxAppendLinesInResultWindow->isChecked())
    {
        ui->textEditLineList->clear();
    }
    ui->textEditResultFileList->clear();
    int currentFileNumber = 0;
    for(auto fileName : fileList)
    {
        QApplication::processEvents();
        if(m_stopSearchFlag == true)
        {
            break;
        }
        searchLinesInTheFile(fileName, lineRegExp);

        QString statusBarMessage;
        QTextStream out(&statusBarMessage);
        currentFileNumber++;
        out << "Line search. " << "File " << currentFileNumber << "/" << fileList.count();
        m_pStatusBarLabel->setText(statusBarMessage);
    }

    setSearchActiveStatus(false);
}

void MainWindow::slotComplexFind()
{
    slotStartFileSearch();
    slotStartLineSearch();
}

void MainWindow::slotStopSearch()
{
    m_stopSearchFlag = true;
}

void MainWindow::slotSaveAsPreset()
{
    bool ok;
    QString presetName = QInputDialog::getText(
                this, tr("New preset dialog"), tr("PresetName:"),
                QLineEdit::Normal, "", &ok);
    if (!ok || presetName.isEmpty())
    {
        return;
    }

    auto items = ui->listWidgetPresets->findItems(presetName, Qt::MatchFixedString);
    if(!items.isEmpty())
    {
        handleError("Preset with the same name already exists.");
        return;
    }

    writePresetSettings(presetName);
    readPresetSettings(presetName);
}

void MainWindow::slotSavePreset()
{
    QListWidgetItem * currentItem = ui->listWidgetPresets->currentItem();

    if(currentItem == nullptr)
    {
        return;
    }

    writePresetSettings(currentItem->text());
    readPresetSettings(currentItem->text());
}

void MainWindow::slotLoadPreset(QListWidgetItem *activeItem)
{
    if(activeItem == nullptr)
    {
        handleError("Preset is not select in the preset tab");
        return;
    }

    readPresetSettings(activeItem->text());
}

void MainWindow::slotLoadActivePreset()
{
    QListWidgetItem * currentItem = ui->listWidgetPresets->currentItem();

    if(currentItem == nullptr)
    {
        handleError("Preset is not select in the preset tab");
        return;
    }

    readPresetSettings(currentItem->text());
}

void MainWindow::slotRemoveActivePreset()
{
    QListWidgetItem * currentItem = ui->listWidgetPresets->currentItem();

    if(currentItem == nullptr)
    {
        handleError("Preset is not select in the preset tab");
        return;
    }

    m_pSettings->beginGroup(currentItem->text());
    m_pSettings->remove(""); //removes the group, and all it keys
    m_pSettings->endGroup();
    ui->listWidgetPresets->removeItemWidget(currentItem);
    delete currentItem;
}

void MainWindow::slotFileListAsSourceStateChanged(int)
{
    bool useSearchInFileSystem = !isFileListAsSourceFlagActive();

    ui->lineEditRootPath->setEnabled(useSearchInFileSystem);
    ui->buttonRootPathBrowse->setEnabled(useSearchInFileSystem);
}

void MainWindow::slotShowIgnoreFiltersStateChanged(int state)
{
    Qt::CheckState stateEnum = (Qt::CheckState)state;

    if(stateEnum == Qt::Unchecked)
    {
        ui->groupBoxFileIgnoreMask->hide();
    }
    else
    {
        ui->groupBoxFileIgnoreMask->show();
    }
}

void MainWindow::slotOnSelectionChanged()
{
    QTextEdit * activeTextEdit = (QTextEdit *)sender();
    QTextCursor textCursor = activeTextEdit->textCursor();
    QString selectedText = textCursor.selectedText();
    m_selectedLines = smartLineSplit(selectedText);
}

void MainWindow::slotTryOpenSelectedFiles()
{
    for (auto line : m_selectedLines)
    {
        QFileInfo textFileInfo(line);
        if(textFileInfo.isFile())
        {
            QProcess proc;
            QFileInfo pathToExe (ui->lineEditExternalFileViewer->text());
            if(!pathToExe.isExecutable())
            {
                handleError("External file viewer setup incorrect");
                return;
            }
            QString pathToExeStr = pathToExe.filePath();
            proc.setProgram(pathToExeStr);
            proc.setArguments(QStringList() << ui->lineEditExtraOptionExternalFileViewer->text()
                              << textFileInfo.filePath());
            proc.startDetached();
        }
    }
}

void MainWindow::slotBrowseExternalFileViewer()
{
    QString filePath = QFileDialog
            ::getOpenFileName(this,
                                   tr("Open File"),
                                   QCoreApplication::applicationDirPath(),
                                   tr("Executable (*.exe)"));
    filePath = QDir::toNativeSeparators(filePath);
    if(!filePath.isEmpty())
    {
        ui->lineEditExternalFileViewer->setText(filePath);
    }
}

void MainWindow::slotWordWrapStateChanged(int)
{
    QTextOption::WrapMode wordWrapMode = ui->checkBoxWordWrapEnabled->isChecked()
            ? QTextOption::WordWrap : QTextOption::NoWrap;

    ui->textEditFileList->setWordWrapMode(wordWrapMode);
    ui->textEditLineList->setWordWrapMode(wordWrapMode);
    ui->textEditResultFileList->setWordWrapMode(wordWrapMode);
}

void MainWindow::setFileTabActive()
{
    ui->tabWidget->setCurrentWidget(ui->tabFileList);
}

void MainWindow::setFileAndLineTabActive()
{
    ui->tabWidget->setCurrentWidget(ui->tabFileAndLineList);
}

void MainWindow::writeApplicationSharedSettings()
{
    bool showIgnoreMaskOptions = ui->checkBoxIgnoreMaskActive->isChecked();
    QString externalFileViewer = ui->lineEditExternalFileViewer->text();
    QString optionExternalFileViewer = ui->lineEditExtraOptionExternalFileViewer->text();
    bool wordWrapEnabled = ui->checkBoxWordWrapEnabled->isChecked();
    bool appendLinesInResultWindow = ui->checkBoxAppendLinesInResultWindow->isChecked();

    m_pSettings->beginGroup(m_appSettingsGroup);
    m_pSettings->setValue("showIgnoreMaskOptions", showIgnoreMaskOptions);
    m_pSettings->setValue("externalFileViewer", externalFileViewer);
    m_pSettings->setValue("optionExternalFileViewer", optionExternalFileViewer);
    m_pSettings->setValue("wordWrapEnabled", wordWrapEnabled);
    m_pSettings->setValue("appendLinesInResultWindow", appendLinesInResultWindow);
    m_pSettings->endGroup();
}

void MainWindow::readApplicationSharedSettings()
{
    readPresetNameSettings();

    m_pSettings->beginGroup(m_appSettingsGroup);
    bool showIgnoreMaskOptions = m_pSettings->value("showIgnoreMaskOptions", false).value<bool>();
    QString externalFileViewer = m_pSettings->value("externalFileViewer", "").value<QString>();
    QString optionExternalFileViewer = m_pSettings->value("optionExternalFileViewer", "").value<QString>();
    bool wordWrapEnabled = m_pSettings->value("wordWrapEnabled", true).value<bool>();
    bool appendLinesInResultWindow = m_pSettings->value("appendLinesInResultWindow", false).value<bool>();
    m_pSettings->endGroup();

    ui->checkBoxIgnoreMaskActive->setChecked(showIgnoreMaskOptions);
    ui->lineEditExternalFileViewer->setText(externalFileViewer);
    ui->lineEditExtraOptionExternalFileViewer->setText(optionExternalFileViewer);
    ui->checkBoxWordWrapEnabled->setChecked(wordWrapEnabled);
    ui->checkBoxAppendLinesInResultWindow->setChecked(appendLinesInResultWindow);
}

void MainWindow::writePresetSettings(QString presetName)
{
    bool fileListAsSourceFlag = ui->checkBoxUseFileListAsSource->isChecked();
    QString rootPath = ui->lineEditRootPath->text();
    QString fileRegExp = ui->lineEditFileRegExp->text();
    QString fileIgnoreExp = ui->lineEditFileIgnoreRegExp->text();
    QString lineRegExp = ui->lineEditLineRegExp->text();
    bool fileRegExpMode = ui->checkBoxIsFileRegExpModeEnabled->isChecked();
    bool fileIgnoreRegExpMode = ui->checkBoxIsFileIgnoreRegExpModeEnabled->isChecked();
    bool lineRegExpMode = ui->checkBoxIsLineRegExpModeEnabled->isChecked();
    bool fileCaseSensitiveMode = ui->checkBoxIsFileRegExpCaseSensitive->isChecked();
    bool fileIgnoreCaseSensitiveMode = ui->checkBoxIsFileIgnoreRegExpCaseSensitive->isChecked();
    bool lineCaseSensitiveMode = ui->checkBoxIsLineRegExpCaseSensitive->isChecked();

    m_pSettings->beginGroup(m_presetsGroup);
    m_pSettings->beginGroup(presetName);
    m_pSettings->setValue("fileListAsSourceFlag", fileListAsSourceFlag);
    m_pSettings->setValue("rootPath", rootPath);
    m_pSettings->setValue("fileRegExp", fileRegExp);
    m_pSettings->setValue("fileIgnoreRegExp", fileIgnoreExp);
    m_pSettings->setValue("lineRegExp", lineRegExp);
    m_pSettings->setValue("fileRegExpMode", fileRegExpMode);
    m_pSettings->setValue("fileIgnoreRegExpMode", fileIgnoreRegExpMode);
    m_pSettings->setValue("lineRegExpMode", lineRegExpMode);
    m_pSettings->setValue("fileCaseSensitiveMode", fileCaseSensitiveMode);
    m_pSettings->setValue("fileIgnoreCaseSensitiveMode", fileIgnoreCaseSensitiveMode);
    m_pSettings->setValue("lineCaseSensitiveMode", lineCaseSensitiveMode);
    m_pSettings->endGroup();
    m_pSettings->endGroup();
}

void MainWindow::readPresetSettings(QString presetName)
{
    readPresetNameSettings();

    m_pSettings->beginGroup(m_presetsGroup);
    m_pSettings->beginGroup(presetName);
    bool fileListAsSourceFlag = m_pSettings->value("fileListAsSourceFlag", false).value<bool>();
    QString rootPath = m_pSettings->value("rootPath", QCoreApplication::applicationDirPath()).value<QString>();
    QString fileRegExp = m_pSettings->value("fileRegExp", "").value<QString>();
    QString fileIgnoreRegExp = m_pSettings->value("fileIgnoreRegExp", "").value<QString>();
    QString lineRegExp = m_pSettings->value("lineRegExp", "").value<QString>();
    bool fileRegExpMode = m_pSettings->value("fileRegExpMode", false).value<bool>();
    bool fileIgnoreRegExpMode = m_pSettings->value("fileIgnoreRegExpMode", false).value<bool>();
    bool lineRegExpMode = m_pSettings->value("lineRegExpMode", false).value<bool>();
    bool fileCaseSensitiveMode = m_pSettings->value("fileCaseSensitiveMode", false).value<bool>();
    bool fileIgnoreCaseSensitiveMode = m_pSettings->value("fileIgnoreCaseSensitiveMode", false).value<bool>();
    bool lineCaseSensitiveMode = m_pSettings->value("lineCaseSensitiveMode", false).value<bool>();
    m_pSettings->endGroup();
    m_pSettings->endGroup();

    ui->checkBoxUseFileListAsSource->setChecked(fileListAsSourceFlag);
    ui->lineEditRootPath->setText(rootPath);
    ui->lineEditFileRegExp->setText(fileRegExp);
    ui->lineEditFileIgnoreRegExp->setText(fileIgnoreRegExp);
    ui->lineEditLineRegExp->setText(lineRegExp);
    ui->checkBoxIsFileRegExpModeEnabled->setChecked(fileRegExpMode);
    ui->checkBoxIsFileIgnoreRegExpModeEnabled->setChecked(fileIgnoreRegExpMode);
    ui->checkBoxIsLineRegExpModeEnabled->setChecked(lineRegExpMode);
    ui->checkBoxIsFileRegExpCaseSensitive->setChecked(fileCaseSensitiveMode);
    ui->checkBoxIsFileIgnoreRegExpCaseSensitive->setChecked(fileIgnoreCaseSensitiveMode);
    ui->checkBoxIsLineRegExpCaseSensitive->setChecked(lineCaseSensitiveMode);

}

void MainWindow::readPresetNameSettings()
{
    m_pSettings->beginGroup(m_presetsGroup);
    ui->listWidgetPresets->clear();
    QStringList presets = m_pSettings->childGroups();
    for(auto preset : presets)
    {
        if(preset != m_defaultPresetName)
        {
            ui->listWidgetPresets->addItem(preset);
        }
    }
    m_pSettings->endGroup();
}

QStringList MainWindow::getFileList()
{
    QStringList fileList = ui->textEditFileList->toPlainText().split('\n');
    if(fileList.last().isEmpty())
    {
        fileList.removeLast();
    }
    return fileList;
}

QRegExp MainWindow::getFileRegExp()
{
    QRegExp fileRegExp(ui->lineEditFileRegExp->text());

    auto caseSensitive = ui->checkBoxIsFileRegExpCaseSensitive->isChecked() ?
                Qt::CaseSensitivity::CaseSensitive :
                Qt::CaseSensitivity::CaseInsensitive;
    fileRegExp.setCaseSensitivity(caseSensitive);

    auto regExpMode = ui->checkBoxIsFileRegExpModeEnabled->isChecked() ?
                QRegExp::RegExp : QRegExp::Wildcard;
    fileRegExp.setPatternSyntax(regExpMode);

    return fileRegExp;
}

QRegExp MainWindow::getFileIgnoreRegExp()
{
    QRegExp fileIgnoreRegExp(ui->lineEditFileIgnoreRegExp->text());

    auto caseSensitive = ui->checkBoxIsFileIgnoreRegExpCaseSensitive->isChecked() ?
                Qt::CaseSensitivity::CaseSensitive :
                Qt::CaseSensitivity::CaseInsensitive;
    fileIgnoreRegExp.setCaseSensitivity(caseSensitive);

    auto regExpMode = ui->checkBoxIsFileIgnoreRegExpModeEnabled->isChecked() ?
                QRegExp::RegExp : QRegExp::Wildcard;
    fileIgnoreRegExp.setPatternSyntax(regExpMode);

    return fileIgnoreRegExp;
}

QRegExp MainWindow::getLineRegExp()
{
    QRegExp lineRegExp(ui->lineEditLineRegExp->text());

    auto caseSensitive = ui->checkBoxIsLineRegExpCaseSensitive->isChecked() ?
                Qt::CaseSensitivity::CaseSensitive : Qt::CaseSensitivity::CaseInsensitive;
    lineRegExp.setCaseSensitivity(caseSensitive);

    auto regExpMode = ui->checkBoxIsFileRegExpModeEnabled->isChecked() ?
                QRegExp::RegExp : QRegExp::Wildcard;
    lineRegExp.setPatternSyntax(regExpMode);

    return lineRegExp;
}

void MainWindow::searchLinesInTheFile(QString fileName, QRegExp lineRegExp)
{
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        bool isAlreadyFoundInThisFile = false;
        int lineNumber = 1;
        QTextStream textFileStream(&inputFile);
        while (!textFileStream.atEnd())
        {
            QString line = textFileStream.readLine();
            if(line.contains(lineRegExp))
            {
                if(!isAlreadyFoundInThisFile)
                {
                    ui->textEditLineList->append(" ");

                    QTextCharFormat fmt;
                    QTextCursor cursor = ui->textEditLineList->textCursor();

                    // new color
                    fmt.setBackground(Qt::lightGray);
                    cursor.mergeCharFormat(fmt);
                    ui->textEditLineList->mergeCurrentCharFormat(fmt);

                    ui->textEditLineList->append(QString("%1").arg(fileName));
                    ui->textEditResultFileList->append(fileName);

                    // restore color
                    fmt.setBackground(Qt::white);
                    cursor.mergeCharFormat(fmt);
                    ui->textEditLineList->mergeCurrentCharFormat(fmt);
                }

                ui->textEditLineList->append(QString("%1: %2").arg(lineNumber).arg(line));

                isAlreadyFoundInThisFile = true;
            }
            lineNumber++;
        }
        inputFile.close();
    }
}

void MainWindow::searchFilesInDirectory()
{
    QString rootDir = ui->lineEditRootPath->text();
    QFileInfo rootDirInfo(rootDir);
    if(!rootDirInfo.isDir())
    {
        handleError("File system file path is not valid");
        return;
    }

    QRegExp fileRegExp = getFileRegExp();
    if(!fileRegExp.isValid())
    {
        handleError(QString("File search mask is not valid: %1")
                    .arg(fileRegExp.errorString()));
        return;
    }

    QRegExp fileIgnoreRegExp = getFileIgnoreRegExp();
    if(!fileIgnoreRegExp.isValid())
    {
        handleError(QString("File ignore mask is not valid: %1")
                    .arg(fileIgnoreRegExp.errorString()));
        return;
    }

    setSearchActiveStatus(true);
    setFileTabActive();
    startSearchInDirectory(rootDir, fileRegExp, fileIgnoreRegExp);
    setSearchActiveStatus(false);
}

void MainWindow::searchFilesInFileList()
{
    QStringList fileList = getFileList();
    if(fileList.isEmpty())
    {
        handleError("File list is empty");
        return;
    }

    QRegExp fileRegExp = getFileRegExp();
    if(!fileRegExp.isValid())
    {
        handleError(QString("File search mask is not valid: %1")
                    .arg(fileRegExp.errorString()));
        return;
    }

    QRegExp fileIgnoreRegExp = getFileIgnoreRegExp();
    if(!fileRegExp.isValid())
    {
        handleError(QString("File ignore mask is not valid: %1")
                    .arg(fileRegExp.errorString()));
        return;
    }

    setSearchActiveStatus(true);
    setFileTabActive();

    int scanFileNumber = 0;
    int foundFileNumber = 0;
    int ignoredFileNumber = 0;
    bool anyLineFound = false;
    for(auto filePath : fileList)
    {
        auto filePathMatch = getFilePathMatch(filePath, fileRegExp, fileIgnoreRegExp);
        switch(filePathMatch)
        {
        case FileMatch::Matched:
            if(!foundFileNumber)
            {
                ui->textEditFileList->clear();
            }
            ui->textEditFileList->append(filePath);
            foundFileNumber++;
            anyLineFound = true;
            break;
        case FileMatch::Ignored:
            ignoredFileNumber++;
        case FileMatch::NotMatched:
        default:
            break;
        }

        scanFileNumber++;

        QString statusBarMessage;
        QTextStream out(&statusBarMessage);
        out << "File search in file list. Scanned: " << scanFileNumber << "; Found: " << foundFileNumber
            << "; Ignored: " << ignoredFileNumber;
        m_pStatusBarLabel->setText(statusBarMessage);
    }

    if(anyLineFound == false)
    {
        handleError("Nothing found");
    }

    setSearchActiveStatus(false);

}

bool MainWindow::isFileListAsSourceFlagActive()
{
    Qt::CheckState stateEnum = ui->checkBoxUseFileListAsSource->checkState();

    if(stateEnum == Qt::Unchecked)
        return false;

    return true;
}

MainWindow::FileMatch MainWindow::getFilePathMatch(QString filePath, QRegExp fileRegExp, QRegExp fileIgnoreRegExp)
{
    if(isFileNameMatch(filePath, fileRegExp))
    {
        if(ui->checkBoxIgnoreMaskActive->isChecked())
        {
            if(!fileIgnoreRegExp.pattern().isEmpty() &&
                    isFileNameMatch(filePath, fileIgnoreRegExp))
            {
                return FileMatch::Ignored;
            }
        }

        return FileMatch::Matched;
    }

    return FileMatch::NotMatched;
}
