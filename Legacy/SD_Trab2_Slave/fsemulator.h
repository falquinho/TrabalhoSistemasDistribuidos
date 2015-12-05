#ifndef FSEMULATOR_H
#define FSEMULATOR_H
#include <qstring.h>

class FSEmulator
{
public:
    QString root_path;
    FSEmulator();
    int createFile(char *recv_mess);
    int createDirectory(char *recv_mess);
    int removeFile(char *recv_mess);
};

#endif // FSEMULATOR_H
