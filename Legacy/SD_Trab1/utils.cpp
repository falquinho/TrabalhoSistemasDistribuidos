#include "utils.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int validadeInput(int argc, char **argv){
    if (argc != 4){
        cout << "Invalid arguments. Usage is './bin server_id server_priority' 'address'\n";
        cout << "where server_id is between [1..1000] and server priority between[1..100]\n";
        return 0;
    }
    else {
        int id = atoi(argv[1]);
        if (id < 1 || id > 1000){
            cout << "Invalid argument: id must be in interval 1..1000\n";
            return 0;
        }
        id = atoi(argv[2]);
        if (id < 1 || id > 100){
            cout << "Invalid argument: priority must be in interval 1..100\n";
            return 0;
        }
    }
    return 1;
}
