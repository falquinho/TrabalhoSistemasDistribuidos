#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <qstringlist.h>
#include <qvector.h>

typedef struct Folder{
    QString name;
    QVector<Folder> sub_folders;
    QStringList files;
}Folder;

class Directory
{
public:
    Folder root;
    QString working_dir;
    const Folder *work_folder;
    //
    Directory();
    int chDir(QString dir);
    int list();
};

#endif // DIRECTORY_H
