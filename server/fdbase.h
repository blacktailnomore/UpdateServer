#ifndef FDBASE_H_INCLUDED
#define FDBASE_H_INCLUDED

#include <unistd.h>
#include <arpa/inet.h>
#include <string>
using std::string;

typedef sockaddr_in SOCKADDRIN;

class FdBase
{
public:
    FdBase();
    ~FdBase();
public:
    void setclientfd(int newfd);
    void setclientaddr(SOCKADDRIN saddr);
    void closefd(bool mclose=false);

    inline int getclientfd(){return fd;}
    inline SOCKADDRIN getclientaddr(){return client_addr;}
private:
    int fd;
    SOCKADDRIN client_addr;
};

#endif // FDBASE_H_INCLUDED
