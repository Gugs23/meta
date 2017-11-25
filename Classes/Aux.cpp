#include "Instance.hpp"

Instance Instance::localSearch(){
    double value = 0, atual, melhor;
    pair<int, int> best;
    int i1, i2, j1, j2;

    for(int i = 0; i < rota.size() - 1; i++){
        value += custoArestas[rota[i].getId()][rota[i+1].getId()];
    }
    melhor = value;
    best.first = -1;
    best.second = -1;
    for(int i = 0; i < rota.size() - 1; i++){
        i1 = rota[i].getId();
        i2 = rota[i + 1].getId();
        for(int j = i + 2; j < rota.size() - 1; j++){
            j1 = rota[j].getId();
            j2 = rota[j + 1].getId();
            atual = value - custoArestas[i1][i2] - custoArestas[j1][j2];
            atual += custoArestas[i1][j1] + custoArestas[i2][j2];
        }
    }
}