#ifndef _FIND_FILE_H_
#define _FIND_FILE_H_

#include <fstream>
#include <string>
#include <map>
#include <vector>
using std::string;
using std::vector;

class FileBase
{
public:
	virtual const char* getdir() = 0;
protected:
	std::string _dir;
	std::string _filename;
};

typedef std::map<std::string, std::string> File_MD5;
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
	virtual const char* getdir() { return _dir.c_str(); }
	vector<string>& getFiles(string dir);
	File_MD5& calfile_md5();
	//vector<string>& calfile_md5();
private:
	std::ifstream _filein;
	vector<string> _allfilename;
	//vector<string> _allfilemd5;
	File_MD5 _file_md5;
};

#endif
