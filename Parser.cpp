#include "Parser.hpp"

MetaParser::MetaParser(string &s){
    fstream arq(s.c_str());
    int vertices, passageiros, capacidade, edgeDesc;

    arq >> vertices >> passageiros >> capacidade >> edgeDesc;
}