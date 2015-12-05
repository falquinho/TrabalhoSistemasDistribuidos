#include "errorhandling.h"
#include <sp.h>
#include <iostream>

using namespace std;

void conciseConnectionError(int code){
    cout << "An error occurred while attempting to connect!\n";
    cout << "Error code: " << code << endl;
    //
    switch (code) {
        case ILLEGAL_SPREAD:
            cout << "spread name given to connect to was illegal for some reason.\n";
        case COULD_NOT_CONNECT:
            cout << "lower level socket calls failed to allow a connection ";
            cout << "to the specified spread daemon right now.\n";
        case CONNECTION_CLOSED:
            cout << "during communication to establish the connection errors occured and the setup could not be completed.\n";
        case REJECT_VERSION:
            cout << "the daemon or library has a version mismatch.\n";
        case REJECT_NO_NAME:
            cout << "no user private name was provided.\n";
        case REJECT_ILLEGAL_NAME:
            cout << "name provided violated some requirement (length or used an illegal character).\n";
        case REJECT_NOT_UNIQUE:
            cout << "name provided is not unique on this daemon.\n";
    }
}

void conciseReceiveError(int code){
    //
    switch (code) {
        case ILLEGAL_SESSION:
            cout << "the mbox given to receive on was illegal.\n";
        case ILLEGAL_MESSAGE:
            cout << "the message had an illegal structure, like a scatter not filled out correctly.";
        case CONNECTION_CLOSED:
            cout << "during communication to receive the message communication errors occured and the receive could not becompleted.\n";
        case BUFFER_TOO_SHORT:
            cout << "the message body buffer was too short to hold the message being received.\n";
        case GROUPS_TOO_SHORT:
            cout << "the groups buffer was too short to hold the groups list or member list being received.\n";
    }
}
