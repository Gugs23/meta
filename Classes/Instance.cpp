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
    int index = 0;
	int atual = listaCidades[0].getId();
	rota.push_back(listaCidades[index]);
	listaCidades.erase(listaCidades.begin() + index);
	while(rota.size() < vertices) {
		vector<Dupla> aux;
		for(int i = 0; i < listaCidades.size(); i++){
			aux.push_back(Dupla(listaCidades[i].getId(), custoArestas[listaCidades[i].getId()][atual].first, i));
		}
		sort(aux.begin(), aux.end());
		int random = rand()%3;
		atual = aux[random].id;
		rota.push_back(listaCidades[aux[random].index]);
		listaCidades.erase(listaCidades.begin() + aux[random].index);
	}
}

Instance Instance::localSearch(){
    Instance anterior = *this;

    double value = 0, atual, melhor;
    pair<int, int> best;
    int i1, i2, j1, j2;

    for(int i = 0; i < rota.size() - 1; i++){
        value += custoArestas[rota[i].getId()][rota[i+1].getId()].first;
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
            atual = value - custoArestas[i1][i2].first - custoArestas[j1][j2].first;
            atual += custoArestas[i1][j1].first + custoArestas[i2][j2].first;
            //cout << "Comparando " << atual << " " << melhor << endl;
            if(atual < melhor){
                melhor = atual;
                best.first = i;
                best.second = j;
            }
        }
    }

    vector<Cidade> novaRota;

    if(best.first != -1 && best.second != -1){
        cout << "Trocou " << best.first << " " << best.second << endl;
        for(int i = 0; i <= best.first; i++){
            novaRota.push_back(rota[i]);
        }
        for(int i = best.second; i > best.first; i--){
            novaRota.push_back(rota[i]);
        }
        for(int i = best.second + 1; i < rota.size(); i++){
            novaRota.push_back(rota[i]);
        }
    }

    rota = novaRota;

    return anterior;
}

bool* Instance::darwin() {
	vector<Passageiro> l;
	bool * candidatos = new bool[numPass];
	
	for(int i = 0; i < numPass; i++) {
		candidatos[i] = false;
	}
	
	for(int i = 0; i < rota.size(); i++) {
		Cidade c = rota[i];
		vector<int> deletor;		
		for(int j = 0; j < l.size(); j++) {	
			l[j].setTarifa(l[j].getTarifa() - (custoArestas[rota[i].getId()][rota[i-1].getId()].first)/4);
			if(l[j].getTarifa() < 0) {
				deletor.push_back(j);
			} else if(c.getId() == l[j].getDesembarque()) {
				deletor.push_back(j);
				candidatos[l[j].getId()-1] = true;
			}
		}
		while(deletor.size() > 0) {
			l.erase(l.begin() + deletor[deletor.size()-1]);
			deletor.erase(deletor.end()-1);
		}
		Passageiro p = passageiros[c.getPassageiro()];
		l.push_back(p);	
	}
	
	for(int i = 0; i < numPass; i++) {
		cout << candidatos[i] << " ";
	}
	
	return candidatos;
}

void Instance::incluirPassageiros() {
	bool * candidatos = darwin();
	vector<Passageiro> auxiliar = passageiros;
	vector<Passageiro> carro;
	int index = 0;
	incluirPassageiros(candidatos,&auxiliar, index, &carro);
	delete candidatos;
}

void Instance::incluirPassageiros(bool * candidatos, vector<Passageiro> * auxiliar, int index, vector<Passageiro> * carro) {
	if(index == rota.size()) {
		return;
	}
	for(int i = 0; i < tripulacao.size(); i++) {
		tripulacao[i].setTarifa(tripulacao[i].getTarifa() - (custoArestas[rota[index].getId()][rota[index-1].getId()].first)/tripulacao.size());
		if(tripulacao[i].getTarifa()<0) {
			reconstruirTripulacao(index, tripulacao[i].getEmbarque());
			incluirPassageiros(candidatos, auxiliar, tripulacao[i].getEmbarque()+1);
			return;
		}
		if(tripulacao[i].getDesembarque() == rota[index].getId()) {
			tripulacao.erase(tripulacao.begin() + i);
		}
	}
	if (candidatos[cidades[index].getPassageiro()] && carro.size() < lotacao) {
		carro.push_back(auxiliar[cidades[index].getPassageiro()]);
		lotacao++;
	}
	incluirPassageiros(candidatos, auxiliar, index+1);
}

void Instance::reconstruirTripulacao(int pontoDeErro, int pontoDeReconstrucao) {
	for(int i = pontoDeErro; i > pontoDeReconstrucao; i--) {
		int qtdPassageiros = tripulacao.size();
		for(int j = 0; j < tripulacao.size(); j++) {
			tripulacao[j].setTarifa(tripulacao[j].getTarifa() + (custoArestas[rota[i].getId()][rota[i-1].getId()].first)/qtdPassageiros);
			if (tripulacao[j].getEmbarque() == rota[i].getId()) {
				tripulacao.erase(tripulacao.begin() + j);
				j--;
			}			
		}
	}
	tripulacao.erase(tripulacao.end() -1);
}

void Instance::printRota(){
    double soma = 0;
    for(int i = 0; i < rota.size() - 1; i++){
        soma += custoArestas[rota[i].getId()][rota[i+1].getId()].first;
        cout << rota[i].getId() << " ";
    }
    cout << rota[rota.size() - 1].getId() << endl;
    soma += custoArestas[rota[0].getId()][rota[rota.size() - 1].getId()].first;

    cout << "Custo: " << soma << endl;
    cout << "Tamanho: " << rota.size() << endl;
	
	printTripulacao();
}

void Instance::printTripulacao(){
	cout << "Passageiros" << endl;
    for(int i = 0; i < tripulacao.size(); i++){
        cout << tripulacao[i].getId() << " ";
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
