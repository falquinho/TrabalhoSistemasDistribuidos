#include "errorlog.h"
#include <iostream>
#include <sp.h>
using namespace std;

void printError(int errorCode){
    switch (errorCode){
    case ILLEGAL_SPREAD:
        cout << "ILLEGAL SPREAD\n";
        break;
    case COULD_NOT_CONNECT:
        cout << "COULD_NOT_CONNECT\n";
        break;
    case CONNECTION_CLOSED:
        cout << "CONNECTION_CLOSED\n";
        break;
    case REJECT_VERSION:
        cout << "REJECT_VERSION\n";
        break;
    case REJECT_NO_NAME:
        cout << "REJECT_NO_NAME\n";
        break;
    case REJECT_ILLEGAL_NAME:
        cout << "REJECT_ILLEGAL_NAME\n";
        break;
    case REJECT_NOT_UNIQUE:
        cout << "REJECT_NOT_UNIQUE\n";
        break;
    case ILLEGAL_GROUP:
        cout << "ILLEGAL_GROUP\n";
        break;
    case ILLEGAL_SESSION:
        cout << "ILLEGAL_SESSION\n";
        break;
    case ILLEGAL_MESSAGE:
        cout << "ILLEGAL_MESSAGE\n";
        break;
    case BUFFER_TOO_SHORT:
        cout << "BUFFER_TOO_SHORT\n";
        break;
    case GROUPS_TOO_SHORT:
        cout << "GROUPS_TOO_SHORT\n";
        break;
    default:
        cout << "Unknown error!\n";
    }
}
