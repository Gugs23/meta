#include <iostream>
using namespace std;

#include <cstdlib>
#include <ctime>

#include "Instance.hpp"

#include "Parser.hpp"

int main(int argc, char * argv[]){
    srand(time(NULL));
    string name = argv[1];
    name = "instancias/" + name;

    //cout << "Exec request " << name << endl;
    
   double start_clock = clock();

    Instance inicio = MetaParser::getInstance(name);

    
    double valor, valor2;
    Instance solucao = inicio.GRASP(valor);

    //Instance solucao2 = inicio.GRASPRef(valor2);

    double end_clock = clock();

    cout << valor << " " << (end_clock - start_clock) / (double (CLOCKS_PER_SEC)) << endl;

    return 0;
}