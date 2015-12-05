#include "slavecommunicator.h"
#include <iostream>
#include <string>
#include <QStringList>


SlaveCommunicator::SlaveCommunicator(CommunicationManager *comm, FileManager * fm)
{
    communicator = comm;
    file_manager = fm;
}

int SlaveCommunicator::waitOrder()
{
    service s_type = DROP_RECV;
    short int m_type;
    int end_mm;
    char sender[MAX_GROUP_NAME];
    //
    int max_groups = 2;
    int no_groups;
    char groups[max_groups][MAX_GROUP_NAME];
    //
    int m_size = 512;
    char mess[m_size];
    //
    while(1)
    {
        std::cout << "SlaveCommunicator::waitOrder:\n\t" << std::flush;
        std::fill(mess, mess+m_size, 0);
        int res = communicator->receiveMessage(&s_type, sender, max_groups, &no_groups, groups, &m_type,\
                                               &end_mm, m_size, mess);
        if (res < 0)
            break;

        if (m_type == MTYPE_CLIENT_REQUEST)
        {
            std::cout << "received client request!" << std::endl;
            processClientOrder(mess);
        }
        else if (m_type == MTYPE_SERVER_NOTIFICATION)
        {
            std::cout << "received server notification!" << std::endl;
            processServerNotification(mess);
        }
        else if (Is_caused_leave_mess(s_type))
        {
            std::cout << "Caused by Leave" << std::endl;
        }
        else if (Is_caused_disconnect_mess(s_type))
        {
            std::cout << "Caused by Disconnect!" << std::endl;

            membership_info memb_info;
            SP_get_memb_info(mess, s_type, &memb_info);

            std::cout << "\tDisconnected member: " << memb_info.changed_member << std::endl;

            notifyProxy(std::string("unregister ") + memb_info.changed_member);
        }
        else
        {
            std::cout << "Unknown message type!" << std::endl;
        }
    }
}

int SlaveCommunicator::processClientOrder(QString message)
{
    std::cout << "SlaveCommunicator::processClientOrder\n";
    QStringList list = message.split(' ', QString::SkipEmptyParts);
    //
    if (list.at(1) == "mkfile")
    {
        doMkfile(list.at(2), list.at(0));
    }
    else if (list.at(1) == "rmfile")
    {
        doRmfile(list.at(2), list.at(0));
    }
    else if (list.at(1) == "write")
    {
        doWrite(list.at(2), list.at(0));
    }
}

int SlaveCommunicator::processServerNotification(QString message)
{
    std::cout << "SlaveCommunicator::processServerNotification\n";
    QStringList lines = message.split('\n', QString::SkipEmptyParts);
    if (lines.at(0) == "write")
    {
        std::cout << "'write' command!\n";
        writeContent(lines.at(1), lines.at(2));
    }
    else
    {
        std::cout << "Unknown command!\n";
    }
}

int SlaveCommunicator::doMkfile(QString param, QString client)
{
    std::cout << "SlaveCommunicator::doMkfile\n";
    if (file_manager->makeFile(param))
    {
        QString result_mess("commit mkfile ");
        result_mess.append(param);
        communicator->sendMessage("PROXY", RELIABLE_MESS, MTYPE_SLAVE_NOTIFICATION, \
                                  result_mess.size(), result_mess.toLocal8Bit().data());
    }
}

int SlaveCommunicator::doRmfile(QString param, QString client)
{
    std::cout << "SlaveCommunicator::doRmfile\n";
    file_manager->removeFile(param);
}

int SlaveCommunicator::doWrite(QString param, QString client)
{
    std::cout << "SlaveCommunicator::doWrite\n";
    //TO DO
}

int SlaveCommunicator::writeContent(QString file, QString content)
{
    std::cout << "SlaveCommunicator::writeContent\n";
    file_manager->writeFile(file, content);
}

int SlaveCommunicator::notifyProxy(std::string mess)
{
    std::cout << "SlaveCommunicator::notifyProxy:" << std::endl;
    std::cout << "\t" << mess << "\n\t";

    int result = communicator->sendMessage("PROXY", RELIABLE_MESS, MTYPE_SLAVE_NOTIFICATION,\
                                           mess.size(), mess.data());
    return result;
}
