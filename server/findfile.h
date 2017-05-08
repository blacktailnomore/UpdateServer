#ifndef _FIND_FILE_H_
#define _FIND_FILE_H_

#include <fstream>
#include "FileUtil.h"

class FileBase
{
public:
	virtual void setdir(string dir) = 0;

	virtual const char* getdir() = 0;

	virtual bool setfilename(string filename) = 0;

protected:
	string _dir;
	string _filename;
};



class FileSystem :public FileBase
{
public:
	FileSystem();

	FileSystem(string dir);

	FileSystem(string dir,const std::ifstream& in);

    virtual ~FileSystem() { _filein.close(); }
public:
	virtual const char* getdir() { return _dir.c_str(); }

	virtual void setdir(string dir);

	virtual bool setfilename(string filename);

public:
    bool init();

	//vector<string>& calfile_md5();
public:
    bool compareFileVersion();
private:
	std::ifstream _filein;
	vector<string> _allfilename;
	//vector<string> _allfilemd5;
	File_MD5 _file_md5;
};

#endif
