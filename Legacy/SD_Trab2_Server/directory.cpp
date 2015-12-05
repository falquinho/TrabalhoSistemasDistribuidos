#include "directory.h"

Directory::Directory()
{
    root.name = "";
    work_folder = &root;
}

int Directory::chDir(QString dir){
    if (dir.compare(dir)){
        work_folder = &root;
        return 1;
    }
    else {
        int i;
        for (i=0; i<work_folder->sub_folders.size(); i++){
            if (work_folder->sub_folders.at(i).name == dir){
                work_folder = &(work_folder->sub_folders.at(i));
                return 1;
            }
        }
    }
    return 0;
}

int Directory::list(){
    //TO DO
}

