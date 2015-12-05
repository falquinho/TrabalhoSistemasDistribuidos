#include "clientmanager.h"
#include "userinterface.h"
#include "errorlog.h"
#include "wordextractor.h"

ClientManager::ClientManager(CommunicationManager * comm)
{
    communicator = comm;
}

void ClientManager::parseUserInput(String input)
{
    std::cout << "ClientManager::parseUserInput\n";
    if (UserInterface::isInputValid(input))
    {
        String command = WordExtractor::getNthWord(input, ' ', 0);
        if (command == "mkfile")
        {
            sendMkfileRequest(input);
        }
        else if (command == "rmfile")
        {
            sendRmfileRequest(input);
        }
        else if (command == "write")
        {
            sendWriteRequest(input);
        }
    }
}

int ClientManager::sendGeneralRequest(String input)
{
    int r = communicator->sendMessage("PROXY", RELIABLE_MESS, MTYPE_CLIENT_REQUEST,\
                                      input.size(), input.data());
    if (r < 0)
    {
        std::cout << "Failed to send message...";
        printError(r);
        std::cout << "\n";
        return r;
    }
    else
    {
        std::cout << "Successfuly sent message!\n";
        String response = waitNotification();
        std::cout << response << "\n";
    }
}

int ClientManager::sendMkfileRequest(String input)
{
    std::cout << "ClientManager::sendClientRequest\n";
    //
    sendGeneralRequest(input);
}

int ClientManager::sendRmfileRequest(String input)
{
    std::cout << "ClientManager::sendRmfileRequest\n";
    sendGeneralRequest(input);
}

int ClientManager::sendWriteRequest(String input)
{
    std::cout << "ClientManager::sendWriteRequest: ";
    //
    int r = communicator->sendMessage("PROXY", RELIABLE_MESS, MTYPE_CLIENT_REQUEST,\
                                      input.size(), input.data());
    if (r < 0)
    {
        std::cout << "Failed to send message...";
        printError(r);
        std::cout << "\n";
        return r;
    }
    else
    {
        std::cout << "Successfuly sent message!\n";
        String response = waitNotification();
        std::cout << response << "\n";
        if (response == "access granted")
        {
            std::cout << "Please type line to write to file:\n";
            String content = UserInterface::getUserInput();
            String message("release\n");
            message.append(WordExtractor::getNthWord(input, ' ', 1));
            message.append("\n");
            message .append(content);
            //
            communicator->sendMessage("PROXY", RELIABLE_MESS, MTYPE_CLIENT_NOTIFICATION,\
                                      message.size(), message.data());
        }
    }
}

String ClientManager::waitNotification()
{
    std::cout << "ClientManager::waitNotification\n";
    service s_type = DROP_RECV;
    //
    char sender[MAX_GROUP_NAME];
    //
    int no_groups;
    char groups[1][MAX_GROUP_NAME];
    //
    short int m_type = 19;
    int end_mm;
    //
    int m_size = 512;
    char mess[m_size];
    //
    do
    {
        communicator->receiveMessage(&s_type, sender, 1, &no_groups, groups,\
                                     &m_type, &end_mm, m_size, mess);
    } while (m_type != MTYPE_SERVER_NOTIFICATION);
    //
    return String (mess);
}
