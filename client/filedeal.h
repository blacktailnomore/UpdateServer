#ifndef FILEDEAL_H
#define FILEDEAL_H

#include <cstdio>

class FileTcpSet;

class FileDeal:public FileTcpSet
{
public:
    FileDeal();
    ~FileDeal();
private:
   FILE* fp;
};


#endif // FILEDEAL_H
