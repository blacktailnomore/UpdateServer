#ifndef _FIND_FILE_H_
#define _FIND_FILE_H_

#include <fstream>
#include "config.h"
#include <vector>
using std::vector;

class FileBase
{
public:
	virtual bool setdir(string dir) = 0;

	virtual const char* getdir() = 0;

	virtual bool setfilename(string filename) = 0;

    virtual bool isFileValid(string filename) = 0;
protected:
	string _dir;
	string _filename;
};

typedef vector<string>::iterator _Allfileitr;

class FileSystem :public FileBase
{
public:
	FileSystem();

	FileSystem(string dir);

	FileSystem(string dir,const std::ifstream& in);



	static FileSystem* _instance;

public:
	static FileSystem* create(string dir);
    virtual ~FileSystem() { _filein.close(); }
public:
	virtual const char* getdir() { return _dir.c_str(); }

	virtual bool setdir(string dir);

	virtual bool setfilename(string filename);

	virtual bool isFileValid(string filename);
public:
    bool init();

	vector<string>& getFiles(string dir);

	File_MD5& calfile_md5();

	string& getSpecificFilename(string dir,string suffix);
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
