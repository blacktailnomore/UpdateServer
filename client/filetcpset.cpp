#include "filetcpset.h"
#include "protocol.h"
#include <windows.h>
#include "util.h"
#include <QDebug>
using namespace protocol;

FileTcpSet::FileTcpSet(){
    _serverfd=sock_error;
    _ip="";
    _port=0;
    len=sizeof(server_addr);
    bzero(&server_addr,len);
}

FileTcpSet::~FileTcpSet(){
    _serverfd=sock_error;
    _ip="";
    _port=0;
    bzero(&server_addr,len);
}

void FileTcpSet::initclient(){
    WORD version=MAKEWORD(1,1);
    WSADATA wsaData;
    WSAStartup(version,&wsaData);

    setip("192.168.1.116");
    setport(3030);

    char* ip=_ip.toAscii().data();

    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr(ip);
    server_addr.sin_port=htons(_port);
    createsocket();
    if(connectserver()){
        receivemsg();
    }
    qDebug("%s","fail");
}

bool FileTcpSet::createsocket(){
    _serverfd=socket(AF_INET,SOCK_STREAM,0);
    if(_serverfd==sock_error)
        return false;
    return true;
}

bool FileTcpSet::setip(QString ip){
    _ip=ip;
    return true;
}

bool FileTcpSet::setport(short port){
    _port=port;
    return true;
}

bool FileTcpSet::connectserver(){
    if(connect(_serverfd,(LPSOCKADDR)&server_addr,len)==0)
        return true;
    return false;
}

void FileTcpSet::receivemsg(){
//    _Filemsg fmsg;
//    _data* dp=(_data*)malloc(sizeof(fmsg)+sizeof(_data));
//    ::recv(_serverfd,(char*)dp,sizeof(fmsg)+sizeof(_data),0);
//    memcpy(&fmsg,dp->local,sizeof(fmsg));
//    qDebug("name:%s,len:%ld",fmsg.filename,ntohl(dp->len));
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    FILE* fp = fopen("4.jar", "wb");
    int length = 0;
    while ((length=recv(_serverfd, buffer, sizeof(buffer), 0)) > 0) {
        if (fwrite(buffer, 1, length, fp) < length) {
            qDebug("len:%d",length);
            break;
        }
        memset(buffer, 0, sizeof(buffer));
    }
    fclose(fp);
}












