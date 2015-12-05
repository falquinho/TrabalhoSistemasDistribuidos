#include "filemanager.h"
#include <iostream>
#include <QDir>
#include <QTextStream>

FileManager::FileManager(char * root)
{
    if (root_dir.exists(root))
    {
        root_dir.cd(root);
        root_dir.removeRecursively();
        root_dir.cdUp();
    }

    root_dir.mkdir(root);
    root_dir.cd(root);

    std::cout << "root directory:\n" << root_dir.path().toStdString() << "\n";
}


int FileManager::makeFile(QString file_name)
{
    std::cout << "FileManager::makeFile\n";
    //
    removeFile(file_name);
    //
    QString file_path = root_dir.path();
    file_path.append("/");
    file_path.append(file_name);
    //
    QFile file(file_path);
    file.open(QIODevice::ReadWrite);
    file.close();
    //
    return 1;
}

int FileManager::removeFile(QString file_name)
{
    std::cout << "FileManager::removeFile: ";
    if (!root_dir.exists(file_name))
    {
        std::cout << "file does not exists!\n";
        return 1;
    }
    else
    {
        if (root_dir.remove(file_name))
        {
            std::cout << "file removed!\n";
            return 1;
        }
        else
        {
            std::cout << "failed to remove file!\n";
            return 0;
        }
    }
}

int FileManager::writeFile(QString file_name, QString content)
{
    std::cout << "FileManager::writeFile: ";
    QFile file (root_dir.path().append("/").append(file_name));
    if (!file.exists())
    {
        std::cout << "File '"<< file_name.toStdString() << "' does not exists!\n";
        return 0;
    }
    file.open(QIODevice::ReadWrite);
    QTextStream stream (&file);
    stream << content;
    file.close();
    //
    std::cout << "File '"<< file_name.toStdString() << "'' written!\n";
    return 1;
}

std::string FileManager::getFile(QString file_name)
{
    std::cout << "FileManager::getFile: ";
    if (!root_dir.exists(file_name))
    {
        std::cout << "file does not exists!\n";
        return 0;
    }
    else
    {
        QFile file(file_name);
        if (!file.open(QIODevice::ReadWrite))
        {
            std::cout << "failed to open file!\n";
            return 0;
        }
        else
        {
            QByteArray data = file.readAll();
            return data.toStdString();
        }
    }
}
