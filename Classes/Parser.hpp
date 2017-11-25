#ifndef _META_PARSER_H
#define _META_PARSER_H

#include <string>
using std::string;

#include <fstream>
using std::fstream;

#include <utility>
using std::pair;

#include "Instance.hpp"

#include "Passageiro.hpp"

#include "Cidade.hpp"

class MetaParser{
    public:
    
        static Instance getInstance(string &name);

};

#endif