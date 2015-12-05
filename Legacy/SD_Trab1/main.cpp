#include <iostream>
#include <stdlib.h>
#include <sp.h>
#include "communicator.h"
#include "serverinfo.h"
#include "errorhandling.h"
#include "usefuldefines.h"
#include "utils.h"

using namespace std;

int main(int argc, char **argv)
{
    if (!validadeInput(argc, argv))
        return 0;
    //
    cout << "Estabilishing conection to Spread Daemon...\n";
    //
    mailbox mbox;
    char *private_group = (char *)malloc(MAX_GROUP_NAME);
    int result = SP_connect(argv[3], argv[1],1, 1, &mbox, private_group);
    if (result != ACCEPT_SESSION){
        conciseConnectionError(result);
        return 1;
    }
    else {
        cout << "Connected to the Spread Daemon!\n";
        if (SP_join(mbox, GROUP_NAME) != 0){
            cout << "Fail to join group 'SERVERS_GROUP!\n'";
            return 1;
        }
        else{
            cout << "Joined group " << GROUP_NAME << endl;
            //
            ServerInfo info(atoi(argv[1]), atoi(argv[2]), "localhost", argv[3]);
            ServerBank *server_bank = new ServerBank(MAX_NO_SERVERS);
            Communicator comm(mbox, server_bank, &info);
            comm.sendHelloMessage(info.id, info.priority);
            //the listen loop
            while (1){
                result = comm.listen();
                conciseReceiveError(result);
                if (result == 0)
                    break;
            }
        }
    }

    cout << "Disconnecting from Spread Daemon...\n";
    result = SP_disconnect(mbox);
    if (result == ILLEGAL_SESSION){
        cout << "Failed! MessageBox not valid!\n";
        return 1;
    }
    cout << "Disconnected!\n";
    return 0;
}
