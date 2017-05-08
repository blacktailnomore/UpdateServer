#ifndef PROTOCOL_H
#define PROTOCOL_H

namespace protocol{
    #define sock_error (-1)

    typedef struct Filemsg{
        long int size;
        char filename[256];
    }_Filemsg;
    typedef struct data{
        int len;
        char local[0];
    }_data;
};

#endif // PROTOCOL_H
