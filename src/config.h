#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "thirdlib/tinyxml.h"
#include <string>
#include <map>
#include "commondef.h"
using std::string;
using std::map;


typedef map<string, string> File_MD5;
typedef map<string, string>::iterator File_MD5_ITR;

class MConfig
{
private:
	MConfig();
	static MConfig* _instance;
public:
    static MConfig* create();
	~MConfig();
public:
    bool init(string& filename);

    //bool run(string filename,string version,File_MD5&);

	bool openXML(string& filename);

	bool createXML(string& filename,string version,File_MD5&);

	TiXmlDocument* getDoc();

    TiXmlElement* getNodebyName(TiXmlElement* e_,string& NodeName);

	void createtest();
private:
	TiXmlDocument*		_xDoc;			//整个XML文档
	TiXmlDeclaration*	_xDeclare;		//声明
	TiXmlElement*		_xRoot;			//根节点
	//TiXmlComment*		_xComm;			//注释
	bool                isExist;
};

#endif
