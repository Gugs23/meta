#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc, char * argv[]){
    fstream arq(argv[1]);

    if(arq.fail()){
        cout << "Impossivel abrir arquivo de lista de execucao." << endl;
        return 1;
    }

    string name, comando;

    while(arq >> name){
        comando = "Classes/Teste " + name;
        system(comando.c_str());
    }

    return 0;
}