#include "servermanager.h"
#include <iostream>
#include <QString>
#include <QStringList>

ServerManager::ServerManager(CommunicationManager * comm)
{
    communicator = comm;
}

int ServerManager::listenRequests()
{
    char sender[MAX_GROUP_NAME];
    //
    int max_groups = 16;
    int no_groups;
    char groups[max_groups][MAX_GROUP_NAME];
    //
    service s_type = DROP_RECV;
    short int m_type;
    int end_mm;
    //
    int m_size = 256;
    char mess[m_size];
    //
    while (true)
    {
        std::fill(mess, mess+m_size, 0);
        int result = communicator->receiveMessage(&s_type, sender, max_groups, &no_groups,\
                                                  groups, &m_type, &end_mm, m_size, mess);
        if (result < 0)
        {
            std::cout << "listenRequests failed...\n";
            return result;
        }
        else
            parseMessage(m_type, sender, mess);

    }
}

void ServerManager::parseMessage(short int m_type, String sender, String mess)
{
    std::cout << "ServerManager::parseMessage : ";
    if (m_type == MTYPE_CLIENT_REQUEST)
    {
        std::cout << "Message type is CLIENT_REQUEST\n";
        processClientRequest(sender, mess);
    }
    else if (m_type == MTYPE_SLAVE_NOTIFICATION)
    {
        std::cout << "Message type is SLAVE_NOTIFICATION\n";
        processSlaveNotification(sender,  mess);
    }
    else if (m_type == MTYPE_CLIENT_NOTIFICATION)
    {
        std::cout << "Message type is CLIENT_NOTIFICATION\n";
        QStringList l = QString(mess.data()).split('\n', QString::SkipEmptyParts);
        performRelease(sender, l.at(1).toStdString(), l.at(2).toStdString());
    }
    else
    {
        std::cout << "Unknown Message Type!\n";
    }
}

void ServerManager::notify(String destination, String message)
{
    std::cout << "ServerManager::notify: "<< destination << "\n\t" << std::flush;
    communicator->sendMessage(destination.data(), RELIABLE_MESS, MTYPE_SERVER_NOTIFICATION, \
                              message.length(), message.data());
}

void ServerManager::processClientRequest(String client, String message)
{
    std::cout << "SlaveManager::processClientRequest :\n\t" << std::flush;
    if (slaves_pool.noOfSlaves() == 0)
    {
        std::cout << "Failed: no known slaves...\n";
        notify(client, "Failed: no known slaves!");
        return;
    }
    //
    QStringList req = QString(message.data()).split(' ', QString::SkipEmptyParts);
    if (req.at(0) ==  "mkfile")
    {
        performMakefile(client, req.at(1).toStdString(), req.at(2).toInt());
    }
    else if (req.at(0) == "rmfile")
    {
        performRemove(client ,req.at(1).toStdString());
    }
    else if (req.at(0) == "write")
    {
        performWrite(client, req.at(1).toStdString());
    }
    else if (req.at(0) == "release")
    {
        performRelease(client, req.at(1).toStdString(), req.at(2).toStdString());
    }
}

void ServerManager::performMakefile(String client, String filename, int copies)
{
    std::cout << "ServerManager::performMakefile:\n";
    if (resource_manager.exists(filename))
    {
        std::cout << "File already exists. Cant override!" << std::endl;
        notify(client, "Failed: file already exists!");
    }
    else
    {
        int i = copies;
        if (i > slaves_pool.noOfSlaves())
            i = slaves_pool.noOfSlaves();

        String message = client;
        message.append(" ").append("mkfile ").append(filename);
        //std::cout << "Message to send:\n" << message << "\n";

        while (i > 0)
        {
            std::cout << "\t";
            String curr_slave = slaves_pool.getNextSlave();

            std::cout << "\tSending message to slave '" << curr_slave << "\n\t";
            communicator->sendMessage(curr_slave.data(), RELIABLE_MESS, MTYPE_CLIENT_REQUEST,\
                                      message.size(), message.data());

            i--;
        }
        std::cout << "\tAll messages sent!" << std::endl;
        notify (client, "File created!");
    }
}

void ServerManager::performRemove(String client, String filename)
{
    //remove o registro do arquivo
    //para cada slave que tem o recurso enviar uma requisiçao de deleçao
    std::cout << "ServerManager::performRemove" << std::endl;
    if (!resource_manager.exists(filename))
    {
        std::cout << "\tFile does not exists!" << std::endl;
        notify(client, "File does not exists!");
    }
    else
    {
        Resource res = resource_manager.getResource(filename);
        int i;
        for (i=0; i<res.location.size(); i++)
        {
            String slave = res.location.at(i);

            String mess = client;
            mess.append(" rmfile ");
            mess.append(filename);

            std::cout << "\t" << std::flush;
            communicator->sendMessage(slave.data(), RELIABLE_MESS, \
                                      MTYPE_CLIENT_REQUEST, mess.size(), mess.data());
        }
        resource_manager.removeResource(filename);

        std::cout << "\tFile removed!" << std::endl;
        notify(client, "File removed!");
    }
}

void ServerManager::performWrite(String client, String filename)
{
    //se o recurso nao estiver travado mando permissao para escrever pro cliente
    std::cout << "ServerManager::performWrite:" << std::endl;
    if (!resource_manager.exists(filename))
    {
        std::cout << "\tFile does not exists!" << std::endl;
        notify(client, "File does not exists!");
    }
    else
    {
        if (resource_manager.isLocked(filename))
        {
            std::cout << "\tFile is locked for writing!\n\t" << std::flush;
            notify(client, "File is locked!");
        }
        else
        {
            std::cout << "\tLocking file for write!\n\t" << std::flush;
            resource_manager.lockResource(filename);
            notify(client, "access granted");
        }
    }
}

void ServerManager::performRelease(String client, String filename, String content)
{
    //TODO
    //replica a mudança para todos os slaves que tem o recurso
    //libera a trava do recurso
    std::cout << "ServerManager::performRelease: ";
    Resource res = resource_manager.getResource(filename);
    resource_manager.unlockResource(filename);
    //
    String mess = "write\n";
    mess.append(filename).append("\n");
    mess.append(content);
    //
    int i;
    for (i=0; i<res.location.size(); i++)
    {
        notify(res.location.at(i), mess);
    }
}

void ServerManager::processSlaveNotification(String slave, String message)
{
    std::cout << "ServerManager::processSlaveNotification:" << std::endl;
    QStringList header = QString (message.data()).split(' ', QString::SkipEmptyParts);
    std::cout << "\tSlave Request: " << header.at(0).toStdString() << std::endl;

    if (header.at(0) == "register")
    {
        std::cout << "\t";

        slaves_pool.registerSlave(header.at(1).toStdString());
    }
    else if (header.at(0) == "unregister")
    {
        std::cout << "\tUnregistering Slave:\n\t" << std::flush;

        slaves_pool.removeSlave(header.at(1).toStdString());

        std::cout << "\t";
        resource_manager.removeLocation(header.at(1).toStdString());
    }
    else if (header.at(0) == "commit")
    {
        if (header.at(1) == "mkfile")
        {
            std::cout << "\tCommiting 'mkfile'" << std::endl;
            resource_manager.addResource(header.at(2).toStdString(), slave);
        }
        else if (header.at(1) == "rmfile")
        {
            std::cout << "\tCommiting 'rmfile'" << std::endl;
            resource_manager.removeResource(header.at(2).toStdString());
        }
        else if (header.at(1) == "write")
        {
            //
        }
    }
}
