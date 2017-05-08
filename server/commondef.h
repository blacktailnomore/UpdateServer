#ifndef _COMMONDEF_H_
#define _COMMONDEF_H_

#include <vector>
#include <map>
#include <string>
using std::string;
using std::vector;
using std::map;

#define _CONT(x) x

#define _FILEN _CONT("fileconfig.xml")
#define _FILES _CONT("server.xml")
#define _CONFPATH _CONT("config/")

typedef vector<string>                  _ALLfile;
typedef vector<string>::iterator        _Allfileitr;
typedef map<string, string>             File_MD5;
typedef map<string, string>::iterator   File_MD5_ITR;

#endif
