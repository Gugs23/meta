#include "Parser.hpp"

Instance MetaParser::getInstance(string &name){
    fstream arq(name.c_str());

    if(arq.fail()){
        cout << "Impossível abrir arquivo " << name << endl;
        throw 1;
    }

    double desc;
    int v1, v2;

    Instance::instanceName = name;

    arq >> Instance::vertices >> Instance::numPass >> Instance::lotacao >> Instance::edgeDesc;
    
    pair<double, double> ** mat = new pair<double, double> * [Instance::vertices];

    for(int i = 0; i < Instance::vertices; i++){
        mat[i] = new pair<double, double> [Instance::vertices];
        for(int j = 0; j < Instance::vertices; j++){
            mat[i][j].first = 0;
            mat[i][j].second = 0;
        }
    }

    for(int i = 0; i < Instance::edgeDesc; i++){
        arq >> desc >> v1 >> v2;
        mat[v1][v2].second = desc;
        mat[v2][v1].second = desc;
    }

    for(int i = 0; i < Instance::vertices; i++){
        for(int j = 0; j < Instance::vertices; j++){
            arq >> mat[i][j].first;
        }
    }

    for(int i = 0; i < Instance::vertices; i++){
        Instance::cidades.push_back(Cidade(i));
    }

    for(int i = 0; i < Instance::numPass; i++){
        arq >> desc >> v1 >> v2;
        Instance::passageiros.push_back(Passageiro(desc, v1, v2));
        Instance::cidades[v1].setPassageiro(i);
    }

    Instance::custoArestas = mat;

    Instance input;

    return input;
}