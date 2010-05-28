// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RosHeader.h"

#include <yarp/os/Bytes.h>
#include <yarp/os/impl/NetType.h>
#include <yarp/os/impl/Name.h>

using namespace yarp::os::impl;
using namespace yarp::os;
using namespace std;

void RosHeader::appendInt(char *&buf,int x) {
    Bytes bytes(buf,4);
    NetType::netInt(x,bytes);
    buf += 4;
}

void RosHeader::appendString(char *&buf,const string& str) {
    memcpy(buf,str.c_str(),str.length());
    buf += str.length();
}


string RosHeader::showMessage(string s) {
    string result = "";
    for (unsigned int i=0; i<s.length(); i++) {
        char buf[256];
        char ch = s[i];
        sprintf(buf, "%c (%d) ", (ch>=' ')?ch:'.', ch);
        result += buf;
    }
    return result;
}

string RosHeader::writeHeader() {
    size_t len = 0;
    for (map<string,string>::iterator it = data.begin();
         it!=data.end(); it++) {
        string key = it->first;
        string val = it->second;
        len += 4 + key.length() + 1 + val.length();
    }
    string result(len,'\0');
    char *buf = (char *)result.c_str();
    for (map<string,string>::iterator it = data.begin();
         it!=data.end(); it++) {
        string key = it->first;
        string val = it->second;
        appendInt(buf,key.length()+1+val.length());
        appendString(buf,key);
        appendString(buf,string("="));
        appendString(buf,val);
    }
    return result;
}


bool RosHeader::readHeader(const string& bin) {
    unsigned int len = bin.length();
    char *at = (char*) bin.c_str();

    while (len>0) {
        Bytes bytes(at,4);
        int slen = NetType::netInt(bytes);
        at += 4;
        len -= 4;
        string keyval(at,slen);
        printf("keyval %s\n", keyval.c_str());
        at += slen;
        len -= slen;
    }
    return true;
}
