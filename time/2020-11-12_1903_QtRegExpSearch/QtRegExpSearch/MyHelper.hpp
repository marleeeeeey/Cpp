#pragma once
#include <QStringList>
#include <QFileInfo>
#include <QString>

namespace MyHelper
{

bool isFileNameMatch(QString filePath, QRegExp regExp)
{
    QFileInfo info(filePath);
    QString fileName = info.fileName();
    return fileName.contains(regExp);
}

bool isLineMatch(QString str, QRegExp regExp)
{
    return str.contains(regExp);
}

QStringList smartLineSplit(QString string)
{
    QString lineEndSymbolsRegExp;
    lineEndSymbolsRegExp.append("[\n\r").append(QChar::ParagraphSeparator).append(']');
    return string.split(QRegExp(lineEndSymbolsRegExp), Qt::SkipEmptyParts);
}

}
