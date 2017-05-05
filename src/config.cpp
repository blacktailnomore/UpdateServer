#include "config.h"

MConfig* MConfig::_instance=NULL;

MConfig::MConfig()
{
    //if(!_xDoc)
    _xDoc = new TiXmlDocument;
    //if(!_xDeclare)
    _xDeclare = new TiXmlDeclaration("1.0", "utf-8", "");
	_xRoot = NULL;
	isExist=false;
}

MConfig::~MConfig()
{

}

MConfig* MConfig::create(){
    if(!_instance)
        _instance=new MConfig;
    return _instance;
}

bool MConfig::init(string& filename){
    isExist=openXML(filename);
    return isExist;
}


bool MConfig::openXML(string& filename)
{
    bool ok=_xDoc->LoadFile(_CONT(filename.c_str()));
    if(ok){
        //log
        return false;
    }
    return true;
}

bool MConfig::createXML(string& filename,string version,File_MD5& file_md5)
{
    openXML(filename);
	//声明
	getDoc()->LinkEndChild(_xDeclare);
	//根节点
	_xRoot = new TiXmlElement(_CONT("fileconfig"));
	getDoc()->LinkEndChild(_xRoot);

	TiXmlElement* v_ = new TiXmlElement(_CONT("version"));
	_xRoot->LinkEndChild(v_);

	TiXmlText* vt_ = new TiXmlText(_CONT(version.c_str()));
	v_->LinkEndChild(vt_);

	for (File_MD5_ITR Fitr = file_md5.begin(); Fitr != file_md5.end(); ++Fitr) {
		TiXmlElement* file_ = new TiXmlElement(_CONT("mod"));
		file_->SetAttribute(_CONT("name"), _CONT(Fitr->first.c_str()));

		TiXmlElement* md5_ = new TiXmlElement(_CONT("md5"));
		file_->LinkEndChild(md5_);

		TiXmlText* md5T_ = new TiXmlText(_CONT(Fitr->second.c_str()));
		md5_->LinkEndChild(md5T_);

		_xRoot->LinkEndChild(file_);
	}

	getDoc()->SetValue(_CONT(filename.c_str()));

	bool ok=getDoc()->SaveFile();
    if(ok)
        return true;
}

TiXmlDocument* MConfig::getDoc(){
    if(_xDoc)
        return _xDoc;
}

TiXmlElement* MConfig::getNodebyName(TiXmlElement* e_,string& NodeName){
    if(NodeName==e_->Value())
        return e_;
    for(TiXmlElement* e=e_->FirstChildElement();e;e=e->NextSiblingElement()){
        if(NodeName==e->Value())
            return e;
        else{
            //printf("%s\n",e->Value());
            getNodebyName(e,NodeName);
        }
    }
}

void MConfig::createtest()
{
	_xDoc->LinkEndChild(_xDeclare);
	_xRoot = new TiXmlElement("fileconfig");
	_xDoc->LinkEndChild(_xRoot);

	TiXmlElement* e2 = new TiXmlElement("version");
	_xRoot->LinkEndChild(e2);

	TiXmlText* v = new TiXmlText("1.0");
	e2->LinkEndChild(v);
	for (int i = 0; i < 10; ++i) {
		TiXmlElement* e3 = new TiXmlElement("file");
		e3->SetAttribute("name", "AdvancedSolarPanel-1.7.10-3.5.1.jar");
		TiXmlElement* e4 = new TiXmlElement("md5");
		e3->LinkEndChild(e4);
		TiXmlText* md5 = new TiXmlText("e37cb1f923c5abb6e2c9b3e96a0efcac");
		e4->LinkEndChild(md5);
		_xRoot->LinkEndChild(e3);
	}

	_xDoc->SetValue(_CONT("test.xml"));

	printf("%d\n", _xDoc->SaveFile());
}
