#include "Parser.hpp"

Instance MetaParser::getInstance(string &name){
    fstream arq(name.c_str());
    Instance input();

    double desc;
    int v1, v2;

    arq >> Instance::vertices >> Instance::passageiros >> Instance::capacidade >> Instance::edgeDesc;
    
    pair<double, double> ** mat = new pair<double, double> * [Instance::vertices];

    for(int i = 0; i < Instance::vertices; i++){
        mat[i] = new pair<double, double> [Instance::vertices];
        for(int j = 0; j < Instance::vertices; j++){
            mat[i][j].first = 0;
            mat[i][j].second = 0;
        }
    }

    for(int i = 0; i < Instance::edgeDesc; i++){
        arq >> desc >>
    }
}