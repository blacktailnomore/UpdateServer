#ifndef FILEUTIL_H_INCLUDED
#define FILEUTIL_H_INCLUDED

#include "config.h"

class FileUtil
{
private:
    FileUtil();
    static FileUtil* _instance;
public:
    static FileUtil* create();
    ~FileUtil();
public:
    bool compareFileVersion();
    bool isFileValid(string filename);
    _ALLfile getFiles(string dir);
private:
    _ALLfile _allfilename;
    string _dir;
};

#endif // FILEUTIL_H_INCLUDED
