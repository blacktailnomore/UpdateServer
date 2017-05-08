#include "FileUtil.h"
#include "config.h"
#ifdef _WIN32
	//#include <direct.h>
	#include <io.h>
#endif
#ifdef linux
	#include <unistd.h>
	#include <dirent.h>
#endif


FileUtil* FileUtil::_instance;

FileUtil* FileUtil::create(){
    if(!_instance)
        _instance=new FileUtil;
    return _instance;
}

FileUtil::FileUtil(){
}

FileUtil::~FileUtil(){
}

bool FileUtil::isFileValid(string filename){
    #ifdef WIN32
	if (_access(filename.c_str(), 0) == 0)
		return true;
#endif
#ifdef linux
	if (access(filename.c_str(),F_OK)==0)
		return true;
#endif
    return false;
}

bool FileUtil::compareFileVersion(){
    TiXmlElement* v_;

    MConfig* mc=MConfig::create();
    string filename_=_CONFPATH;
    filename_+=_FILES;
    string version1_="confversion";
    if(isFileValid(filename_)){
        //log

        v_=mc->getNodebyName(mc->getDoc()->RootElement(),version1_);
        //log
        version1_=v_->GetText();
    }
    filename_.clear();
    filename_+=_CONFPATH;
    filename_+=_FILEN;
    string version2_="modversion";
    if(isFileValid(filename_)){

        v_=mc->getNodebyName(mc->getDoc()->RootElement(),version2_);
        //log
        version2_=v_->GetText();
    }
    if(version1_==version2_)
        return true;
    return false;
}

_ALLfile FileUtil::getFiles(string dir) {
	size_t count = 0;
	_dir = dir;
	if(isFileValid(_dir)){
#ifdef WIN32
        _finddata_t file_;
        string total = dir + "*";
        long lf_ = _findfirst(total.c_str(), &file_);
        //printf("%s\n", file_.name);
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
    }
	//printf("共有文件：%d个\n", count);
	return _allfilename;
}
