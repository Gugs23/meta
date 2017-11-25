#include "Parser.hpp"

Instance MetaParser::getInstance(string &name){
    fstream arq(name.c_str());
    Instance input();

    arq >> Instance::vertices;   
}