#ifndef UTIL_H
#define UTIL_H

#define CONFIGPATH "config/modversion.xml"

static void bzero(void* buf,unsigned int len){
    memset(buf,0,len);
}

#endif // UTIL_H
