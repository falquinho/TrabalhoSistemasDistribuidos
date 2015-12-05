#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QDir>
#include <string>

class FileManager
{
    QDir root_dir;
public:
    FileManager(char * root);
    int makeFile(QString file_name);
    int removeFile(QString file_name);
    std::string getFile(QString file_name);
    int writeFile(QString file_name, QString content);
};

#endif // FILEMANAGER_H
