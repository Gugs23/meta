#ifndef _META_PARSER_H
#define _META_PARSER_H

#include <string>
using std::string;

#include <fstream>
using std::fstream;

#include "Instance.hpp"


class MetaParser{
    public:
    
        static Instance getInstance(string &name);

    private:
        MetaParser(string &);
};

#endif