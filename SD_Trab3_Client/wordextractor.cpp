#include "wordextractor.h"
#include <iostream>
#include <qt5/QtCore/qstring.h>
#include <qt5/QtCore/QStringList>

int WordExtractor::getWordCount(String input, char separator)
{
    QString str(input.data());
    QStringList l = str.split(separator, QString::SkipEmptyParts);
    return l.size();
}

String WordExtractor::getNthWord(String input, char separator, int n)
{
    QString str(input.data());
    QStringList l = str.split(separator, QString::SkipEmptyParts);
    return l.at(n).toStdString();
}
