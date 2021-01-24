#pragma once

#include <QMainWindow>

class QErrorMessage;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QHBoxLayout;
class QSettings;
class QListWidgetItem;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum class FileMatch
    {
        Matched,
        NotMatched,
        Ignored
    };

    void handleError(QString msg);
    void startSearchInDirectory(QString dirStr, QRegExp fileRegExp, QRegExp fileIgnoreRegExp);
    void onFileFound(QString filePath);
    void setSearchActiveStatus(bool b);
    void setFileTabActive();
    void setFileAndLineTabActive();
    void writeApplicationSharedSettings();
    void readApplicationSharedSettings();
    void writePresetSettings(QString presetName);
    void readPresetSettings(QString presetName);
    void readPresetNameSettings();
    QStringList getFileList();
    QRegExp getFileRegExp();
    QRegExp getFileIgnoreRegExp();
    QRegExp getLineRegExp();
    void searchLinesInTheFile(QString fileName, QRegExp lineRegExp);
    void searchFilesInDirectory();
    void searchFilesInFileList();
    bool isFileListAsSourceFlagActive();
    FileMatch getFilePathMatch(QString filePath, QRegExp fileRegExp, QRegExp fileIgnoreRegExp);

    Ui::MainWindow *ui;
    bool m_stopSearchFlag;
    QSettings * m_pSettings;
    QString m_defaultPresetName;
    QString m_presetsGroup;
    QString m_appSettingsGroup;
    QLabel * m_pStatusBarLabel;
    QStringList m_selectedLines;
    QString m_externalApplication;
    QString m_extraOptions;

private slots:
    void slotBrowseRootDirectory();
    void slotStartFileSearch();
    void slotStartLineSearch();
    void slotComplexFind();
    void slotStopSearch();
    void slotSaveAsPreset();
    void slotSavePreset();
    void slotLoadPreset(QListWidgetItem * activeItem);
    void slotLoadActivePreset();
    void slotRemoveActivePreset();
    void slotFileListAsSourceStateChanged(int);
    void slotShowIgnoreFiltersStateChanged(int);
    void slotOnSelectionChanged();
    void slotTryOpenSelectedFiles();
    void slotBrowseExternalFileViewer();
    void slotWordWrapStateChanged(int state);
};

