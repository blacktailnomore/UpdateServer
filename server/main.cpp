#include <iostream>

#include "md5.h"
#include <fstream>
#include "findfile.h"
#include "config.h"
using namespace std;

int main()
{
	//union {
	//	char c[4];
	//	unsigned int s;
	//}un;
	//un.s = 0x67452301;
	//for (size_t i = 0; i<sizeof(unsigned int); ++i)
	//	printf("%d\n", un.c[i]);
	//cout << "===================" << endl;
	//un.s = 0x01234567;
	//for (size_t i = 0; i<sizeof(unsigned int); ++i)
	//	printf("%d\n", un.c[i]);
	//char* filename = "F:\\SingleGames\\MultiMC\\instances\\Infinity Evolved\\minecraft\\mods\\AdvancedSolarPanel-1.7.10-3.5.1.jar";
	//ifstream in;
	//in.open("d:/shader_log.ini",ios::binary);
	string dir = "/home/blacktail/jar/";
	//MD5 strmd5("123");
	//cout << strmd5.toString() << endl;
	MD5 filemd5;
	//filemd5.update(in);
	//cout << filemd5.toString() << endl << "-------------------------------------" << endl;
	//in.close();




	//mc.createtest();
	//mc->createXML(_FILEN, "1.0", mymd5);

#ifdef WIN32
	system("pause");
#endif
	return 0;
}
