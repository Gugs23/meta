#include <iostream>
using namespace std;

#include <cstdlib>
#include <ctime>

#include "Instance.hpp"
#define __MIN(A, B) A < B ? A : B


#include "Parser.hpp"

int main(int argc, char * argv[]){
    srand(time(NULL));
    string name = argv[1];
    name = "instancias/" + name;

    //cout << "Exec request " << name << endl;
    
    double valor, fin;

    double start_clock = clock();

    Instance inicio = MetaParser::getInstance(name);
    Instance solucao = inicio.melhorDoMelhorDoMundo(valor);
    fin = valor;
    for(int i = 0; i < 100; i++){
        //cout << fin << endl;
        solucao = inicio.melhorDoMelhorDoMundo(valor);
        fin = __MIN(fin, valor);
        /* cout << "Current Value: " << fin << endl;
        cout << "Iteration: " << i << endl;
        cout << "Ellapsed time: " << (end_clock - start_clock) / (double (CLOCKS_PER_SEC)) << endl;
        cout << endl << endl; */
    }
    
    double end_clock = clock();

    cout << fin << " " << (end_clock - start_clock) / (double (CLOCKS_PER_SEC))<< endl;

  
    return 0;
}