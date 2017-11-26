#include <iostream>
using namespace std;

#include <cstdlib>
#include <ctime>

#include "Instance.hpp"

#include "Parser.hpp"

int main(){
    srand(time(NULL));
    string name = "../instancias/pcv_cal-50-classe_10-instancia_21.txt";
    Instance inicio = MetaParser::getInstance(name);

    inicio.printRota();
    Instance anterior = inicio.localSearch();

    cout << "Apos LS " << endl;
    cout << "Velha " << endl << endl;
    anterior.printRota();

    cout << endl << endl << " Nova " << endl << endl;
    inicio.printRota();
	
	cout << endl << endl << "Passageiros possiveis: " << endl << endl;
	vector<Passageiro> passageiros = inicio.darwin();
	for(int i = 0; i < passageiros.size(); i++) {
		cout << passageiros[i].getEmbarque() << " ";
	}

    return 0;
}