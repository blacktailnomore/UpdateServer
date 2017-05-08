#include "configmanager.h"
#include "util.h"
#include <QFile>


ConfigManager* ConfigManager::_instance;

ConfigManager::ConfigManager(){

}

ConfigManager::~ConfigManager(){

}

ConfigManager* ConfigManager::create(){
    if(!_instance)
        _instance=new ConfigManager;
    return _instance;
}

QString ConfigManager::readXMLversion(QString &dir){
    if(isXMLvalid(dir)){
        QFile file(dir);

        QDomDocument doc;

        if(!doc.setContent(&file,false))
            return NULL;

        QDomElement root=doc.documentElement();
        if(root.tagName()!="fileconfig"){
            return NULL;
        }
        QString tag_="modversion";
        QDomElement ver_=getNodeByName(root,tag_);
        return ver_.text();
    }
}

bool ConfigManager::isXMLvalid(QString &dir){
    QFile file(dir);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        return false;
    }
    file.close();
    return true;
}

QDomElement ConfigManager::getNodeByName(QDomElement &ele, QString &tagname){
    if(tagname==ele.tagName())
        return ele;
    for(QDomElement e_=ele.firstChildElement();!e_.isNull();e_=e_.nextSiblingElement()){
       if(tagname==e_.tagName())
           return e_;
       else
           getNodeByName(e_,tagname);
    }
    //return ele;
}
