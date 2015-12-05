#include "userinterface.h"
#include "clientmanager.h"
#include "wordextractor.h"
typedef std::string String;

int main(int argc, char *argv[])
{

#if 1
    if (argc != 3)
    {
        std::cout << "Invalid parameters. Correct use is: './a daemon_addr process_id'\n";
        return 1;
    }
    //
    CommunicationManager comm;
    if (comm.openConnection(argv[1], argv[2]) != ACCEPT_SESSION)
    {
        std::cout << "Client failed to connect to the Spread Daemon!\n";
        return 1;
    }
    //
    ClientManager manager(&comm);
    //
    UserInterface::printWelcome();
    while (1){
        String input = UserInterface::getUserInput();
        //
        if (input == "exit" || input == "quit")
            break;
        else if (input == "help")
            UserInterface::printHelp();
        else {
            manager.parseUserInput(input);
        }
    }
    //

    comm.closeConnecion();
#else
    //test area...
    String input = UserInterface::getUserInput();
    int no = WordExtractor::getWordCount(input, ' ');
    std::cout << "No palavras: " << no << "\n";
    int i;
    for (i=0; i < no; i++)
    {
        std::cout << WordExtractor::getNthWord(input, ' ', i) << "\n";
    }
    UserInterface::isInputValid(input);
#endif

    return 0;
}
