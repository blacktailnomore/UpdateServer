#include "findfile.h"
#include "md5.h"
//#ifdef _WIN32
//	//#include <direct.h>
//	#include <io.h>
//#endif
//#ifdef linux
//	#include <unistd.h>
//	#include <dirent.h>
//#endif


FileSystem::FileSystem()
{}

FileSystem::FileSystem(string dir)
{
	_dir = dir;
	_filename = "";
}
FileSystem::FileSystem(string dir,const std::ifstream& in) {
	_dir = dir;
	_filename = "";
}



bool FileSystem::init(){

}


void FileSystem::setdir(string dir) {
	_dir = dir;

}
bool FileSystem::setfilename(string filename) {
	_filename = filename;
	if (!_filename.empty())
		return true;
	return false;
}












