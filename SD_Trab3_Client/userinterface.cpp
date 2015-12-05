#include "userinterface.h"
#include "wordextractor.h"
#include <qt5/QtCore/qstring.h>

std::string UserInterface::getUserInput(){
    std::string input;
    std::cout << ">";
    std::getline(std::cin, input);
    return input;
}

bool UserInterface::isInputValid(String input)
{
    std::cout << "UserInterface::isInputValid : ";
    int no_words = WordExtractor::getWordCount(input, ' ');
    if (no_words >= 2)
    {
        String command = WordExtractor::getNthWord(input, ' ', 0);
        //
        if (command == "mkfile")
        {
            if (no_words != 3)
            {
                std::cout << "Invalid Input: mkfile : not enough parameters\n";
                return false;
            }
            else
            {
                QString num(WordExtractor::getNthWord(input, ' ', 2).data());
                bool ok;
                num.toInt(&ok);
                if (!ok)
                {
                    std::cout << "Invalid Input: mkfile : thrind param not numeral\n";
                    return false;
                }
            }
        }
        else if (command == "rmfile" && no_words != 2)
        {
            std::cout << "Invalid Input : rmfile\n";
            return false;
        }
        else if (command == "write" && no_words != 2)
        {
            std::cout << "Valid Input : write\n";
            return false;
        }
    }
    else
    {
        std::cout << "Invalid Input\n";
        return false;
    }
}

void UserInterface::printWelcome(){
    std::cout << "Welcome to this Simple Distributed File System.\n";
    std::cout << "Type 'help' for a list of avaible commands.\n";
}

void UserInterface::printHelp(){
    std::cout << "Avaible commands:\n";
    std::cout << "'help':\n\tShow this message.\n";
    std::cout << "'exit' or 'quit':\n\tQuit the program.\n";
    std::cout << "'mkfile file no_copies':\n";
    std::cout << "\tCreate the file 'file' replicating it 'no_copies'-times\n";
    std::cout << "'rmfile file':\n";
    std::cout << "\tDelete all replicas of 'file'.\n";
    std::cout << "'write file':\n";
    std::cout << "\tRetrieve file 'file' for writing.\n";
}
