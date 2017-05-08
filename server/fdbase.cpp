#include "fdbase.h"
#include <cstring>

FdBase::FdBase(){}

FdBase::~FdBase(){
    fd=-1;
    memset(&client_addr,0,sizeof(client_addr));
}

void FdBase::setclientfd(int newfd){
    fd=newfd;
}
void FdBase::setclientaddr(SOCKADDRIN saddr){
    client_addr=saddr;
}
void FdBase::closefd(bool mclose){
    if(mclose)
        close(fd);
}
