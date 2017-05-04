#include "findfile.h"
#include "md5.h"
#ifdef _WIN32
	//#include <direct.h>
	#include <io.h>
#endif
#ifdef linux
	#include <unistd.h>
	#include <dirent.h>
#endif

FileSystem* FileSystem::_instance;

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

FileSystem* FileSystem::create(string dir) {
	return _instance;
}

vector<string>& FileSystem::getFiles(string dir) {
	size_t count = 0;
	_dir = dir;
#ifdef WIN32
	_finddata_t file_;
	string total = dir + "*";
	long lf_ = _findfirst(total.c_str(), &file_);
	printf("%s\n", file_.name);
	//printf("%d\n", lf_);
	if (-1 == lf_) {
		//Log日志
		printf("没有找到目录");
	}
	else {
		do {
			if (file_.attrib&_A_SUBDIR)//跳过子目录
				continue;
			//printf("%s\n", file_.name);
			_allfilename.push_back(file_.name);
			count++;

		} while (_findnext(lf_, &file_) == 0);
	}
	_findclose(lf_);
	
#endif
#ifdef linux
	DIR* dir_;
	dirent* ptr_;
	dir_ = opendir(dir.c_str());
	if (!dir_) {
		//Log日志
		printf("%s", "没有找到目录");
		perror("没有找到目录");
	}
	while ((ptr_ = readdir(dir_)) != NULL) {
		if (ptr_->d_type == DT_REG) {
			//printf("%s\n",ptr_->d_name);
			_allfilename.push_back(ptr_->d_name);
			count++;
		}
		else
			continue;
	}
	closedir(dir_);
#endif
	printf("共有文件：%d个\n", count);	
	return _allfilename;
}

File_MD5& FileSystem::calfile_md5() {
	MD5 md5_;
	_Allfileitr fitr;
	ifstream in;
	printf("%s\n", __TIME__);
	for (fitr = _allfilename.begin(); fitr != _allfilename.end(); ++fitr) {
		string absolutepath = _dir + *fitr;
		in.open(absolutepath,std::ios::binary);
		//printf("%s\n", absolutepath.c_str());

		md5_.reset();
		md5_.update(in);
		string md5_str_ = md5_.toString();
		_file_md5.insert(make_pair(*fitr, md5_str_));
		//_allfilemd5.push_back(md5_str_);
		in.close();
	}
	return _file_md5;
}
















