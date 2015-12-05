#include "fsemulator.h"
#include <qdir.h>
#include <qfile.h>
#include <qtextstream.h>
#include <iostream>
using namespace std;

FSEmulator::FSEmulator()
{
    //setup root dir if already not created
    root_path = QDir::currentPath().append("/root/");
    QDir dir (root_path);
    if (!dir.exists()){
        cout << "Root does not exist! Creating it...\n";
        dir.mkdir(root_path);
    }
}

int FSEmulator::createDirectory(char *recv_mess){
    cout << "Creating Directory....\n";
    QStringList args = QString (recv_mess).split("/", QString::SkipEmptyParts);
    QDir dir (root_path);
    int i;
    for (i=1; i<args.size(); i++){
        dir.mkdir(args.at(i));
        if (dir.exists(args.at(i)))
            dir.cd(args.at(i));
        else return 0;
    }
    return 1;
}

int FSEmulator::createFile(char *recv_mess){
    cout << "Creating File...\n";
    QDir dir(root_path);
    QStringList args = QString (recv_mess).split("/", QString::SkipEmptyParts);
    QString file_path = dir.path();
    int i;
    for (i=1; i<args.size()-1; i++){
        if (!dir.cd(args.at(i)))
            return 0;
        file_path.append("/");
        file_path.append(args.at(i));
    }
    file_path.append("/");
    file_path.append(args.at(args.size()-1));
    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly))
        return 0;
    file.close();
    //
    return 1;
}

int FSEmulator::removeFile(char *recv_mess){
    cout << "Removing File...\n";
    QDir dir(root_path);
    QStringList args = QString (recv_mess).split("/", QString::SkipEmptyParts);
    QString file_path = dir.path();
    int i;
    for (i=1; i<args.size()-1; i++){
        if (!dir.cd(args.at(i)))
            return 0;
        file_path.append("/");
        file_path.append(args.at(i));
    }
    file_path.append("/");
    file_path.append(args.at(args.size()-1));
    QFile file(file_path);
    if (!file.remove())
        return 0;
    return 1;
}

