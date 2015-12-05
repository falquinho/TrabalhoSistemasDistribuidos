#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string.h>
#include <iostream>
typedef std::string String;

class UserInterface
{
public:
    static String getUserInput();
    static void printWelcome();
    static void printHelp();
    static bool isInputValid(String input);
};

#endif // USERINTERFACE_H
