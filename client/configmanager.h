#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>
#include <QXmlStreamReader>
#include <QDomDocument>
class ConfigManager
{
private:
    ConfigManager();
    ~ConfigManager();
    static ConfigManager* _instance;
public:
    static ConfigManager* create();
public:
    QString readXMLversion(QString& dir);
    bool isXMLvalid(QString& dir);
    QDomElement getNodeByName(QDomElement& ele,QString& tagname);
private:
    QXmlStreamReader reader;
};

#endif // CONFIGMANAGER_H
