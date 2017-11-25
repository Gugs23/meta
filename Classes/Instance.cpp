#include "Instance.hpp"

int Instance::vertices;

int Instance::numPass;

int Instance::lotacao;

int Instance::edgeDesc;

string Instance::instanceName;

pair<double, double> ** Instance::custoArestas;

vector<Passageiro> Instance::passageiros;

vector<Cidade> Instance::cidades;

Instance::Instance(){
    vector<Cidade> listaCidades = cidades;	
	int atual = listaCidades[0].getId();
	rota.push_back(listaCidades[atual]);
	listaCidades.erase(listaCidades.begin() + atual);
	while(rota.size() < vertices) {
		vector<Dupla> aux;
		for(int i = 0; i < listaCidades.size(); i++){
			aux.push_back(Dupla(listaCidades[i].getId(), custoArestas[listaCidades[i].getId()][atual].first));
		}
		sort(aux.begin(), aux.end());
		int random = rand()%3;
		atual = aux[random].id;
		rota.push_back(listaCidades[atual]);
		listaCidades.erase(listaCidades.begin() + atual);
	}
}

void Instance::printBase(){
    cout << "Numero de Vertices " << vertices << endl;
    cout << "Numero de Passagerios " << numPass << endl;
    cout << "Lotacao " << lotacao << endl;

    cout << "Vertices com desconto " << edgeDesc << endl;

    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            cout << fixed << setprecision(2) << "<" << custoArestas[i][j].first << ", " << custoArestas[i][j].second << "> ";
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0; i < numPass; i++){
        cout << "Passageiro " << i << ": " << passageiros[i].getTarifa() << " " << passageiros[i].getEmbarque() << " " << passageiros[i].getDesembarque() << endl;
    }

    cout << "Espero que não tenha dado merda" << endl;
}
