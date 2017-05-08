#ifndef FILETCPSET_H
#define FILETCPSET_H

#include <winsock2.h>
#include <QString>
//#include <winsock2.h>

class FileTcpSet
{
public:
    FileTcpSet();
    ~FileTcpSet();
    void initclient();
    void receivemsg();
private:
    bool setport(short port);
    bool setip(QString ip);
    bool createsocket();
    bool connectserver();
private:
    unsigned int len;
    SOCKET _serverfd;
    short _port;
    QString _ip;
    sockaddr_in server_addr;
};

#endif // FILETCPSET_H
