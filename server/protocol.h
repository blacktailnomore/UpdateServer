#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED

#define NEWCOMER        0x0001
#define MISSINGFILE     Ox0002

typedef enum FILESTATUS{
    deleted=0,
    added,
    unkown
}_FILESTATUS_;

struct WhichType{
    int type;
};

struct MissingFile{

}

struct Filetransfer{
    long int size;
    char filename[256];

    char verion[5];
};

#endif // PROTOCOL_H_INCLUDED
