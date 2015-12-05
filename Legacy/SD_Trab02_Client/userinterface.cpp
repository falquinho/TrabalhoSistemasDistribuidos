#include "userinterface.hpp"
#include <iostream>
#include <qstring.h>
#include <qstringlist.h>

UserInterface::UserInterface()
{
    working_dir = "";
    cout << "Welcome to SiDiFiS! Type 'help' for a list of commands.\n";
}

int UserInterface::helpScreen(){
    cout << "Commands:\n'help': this screen...\n";
    cout << "'exit: exit this program'";
    cout << "'mkdir dirname': create a directory with name 'dirname'\n";
    cout << "'mkfile filename': create a file with name 'filename'\n";
    cout << "'rmfile': delete a file\n";
    cout << "'list': list content of current working directory\n";
}

int UserInterface::commandLoop(ClientCommunicator *comm){
    while (1){
        cout << working_dir << ">";
        string command;
        getline(cin, command);
        if (command == "exit")
            break;
        else if (command == "")
            continue;
        else
            parseCommand(command, comm);
    }
}

int UserInterface::parseCommand(string command, ClientCommunicator *comm){
    if (command == "help")
        helpScreen();
    else {
        QString str(command.c_str());
        QStringList args = str.split(" ", QString::SkipEmptyParts);
        //
        if (args.at(0) == "mkdir"){
            if (args.size() != 2)
                cout << "Error. Invalid arguments\n";
            else {
                if (args.at(1).contains("/"))
                    cout << "'dirname' cant contain '/'\n";
                else{
                    int resp_len = 0;
                    char response[resp_len];
                    short int resp_type;
                    comm->requestOperation(args.at(1), CREQUEST_MKDIR, resp_len, response, &resp_type);
                    if (resp_type == REQUEST_SUCCESS)
                        cout << "Directory created!\n";
                    else if (resp_type == REQUEST_FAILED)
                        cout << "Failed to create directory!\n";
                }
            }
        }
        //
        else if (args.at(0) == "chdir"){
            if (args.size() != 2)
                cout << "Error. Invalid arguments\n";
            else {
                if (args.at(1).contains("/"))
                    cout << "'dirname' cant contain '/'\n";
                else{
                    int resp_len = 512;
                    char response[resp_len];
                    short int resp_type;
                    comm->requestOperation(args.at(1), CREQUEST_CHDIR, resp_len, response, &resp_type);
                    if (resp_type == REQUEST_SUCCESS)
                        working_dir = response;
                    else if (resp_type == REQUEST_FAILED)
                        cout << "Failed to change directory!\n";
                }
            }
        }
        else if (args.at(0) == "list"){
            if(args.size() != 1)
                cout << "Error: invalid arguments\n";
            else {
                int resp_len = 1024;
                char resp[resp_len];
                short int resp_type;
                comm->requestOperation(args.at(0), CREQUEST_LIST, resp_len, resp, &resp_type);
                if (resp_type == REQUEST_FAILED)
                    cout << "Failed to list files\n";
                else if (resp_type == REQUEST_SUCCESS)
                    cout << resp << endl;
            }
        }
        else if (args.at(0) == "mkfile"){
            if (args.size() != 2)
                cout << "Error: invalid arguments\n";
            else{
                int resp_len = 256;
                char resp[resp_len];
                short int resp_type;
                comm->requestOperation(args.at(1), CREQUEST_MKFILE, resp_len, resp, &resp_type);
                if (resp_type == REQUEST_FAILED)
                    cout << "Failed to create file!\n";
                else if (resp_type == REQUEST_SUCCESS)
                    cout << "file created!\n";
            }
        }
        else if (args.at(0) == "rmfile"){
            if (args.size() != 2)
                cout << "Error: Invalid arguments!\n";
            else {
                int resp_len = 256;
                char resp[resp_len];
                short int resp_type;
                comm->requestOperation(args.at(1), CREQUEST_RMFILE, resp_len, resp, &resp_type);
                if (resp_type == REQUEST_FAILED)
                    cout << "Failed to remove file!\n";
                else if (resp_type == REQUEST_SUCCESS)
                    cout << "File removed!\n";
            }
        }
        else {
            cout << "Invalid command...\n";
        }
    }
}



