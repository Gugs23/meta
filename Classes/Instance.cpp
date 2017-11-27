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
	int mod = vertices / 5;
	rota.push_back(listaCidades[index]);
	listaCidades.erase(listaCidades.begin() + index);
	while(rota.size() < vertices) {
		vector<Dupla> aux;
		for(int i = 0; i < listaCidades.size(); i++){
			aux.push_back(Dupla(listaCidades[i].getId(), custoArestas[listaCidades[i].getId()][atual].first, i));
		}
		sort(aux.begin(), aux.end());
		mod = __MIN(mod, aux.size());
		int random = rand() % mod;
		atual = aux[random].id;
		rota.push_back(listaCidades[aux[random].index]);
		listaCidades.erase(listaCidades.begin() + aux[random].index);
	}
	rota.push_back(cidades[0]);
}

Instance Instance::__switch(int ini, int fim){
	vector<Cidade> novaRota;

	for(int i = 0; i <= ini; i++){
		novaRota.push_back(rota[i]);
	}
	for(int i = fim; i > ini; i--){
		novaRota.push_back(rota[i]);
	}
	for(int i = fim + 1; i < rota.size(); i++){
		novaRota.push_back(rota[i]);
	}

	Instance nova = *this;
	nova.rota = novaRota;

	return nova;
}

Instance Instance::apply2opt(bool &melhora){
	melhora = false;
	rota.erase(rota.begin() + (rota.size() - 1));
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
	
	rota.push_back(rota[0]);

    vector<Cidade> novaRota;

    if(best.first != -1 && best.second != -1){
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
	Instance nova(*this);
	if(novaRota.size() != 0){
		melhora = true;
		nova.rota = novaRota;
	}


    return nova;
}

Instance Instance::localSearch(double & bestValue){
	double atualValue;
	int pior = 0;
	incluirPassageiros();

	bestValue = getValue();

	Instance atual = *this;
	Instance nova = atual;

	bool improve2opt;

	//cout << "Valor Inicial: " << bestValue << endl;
	//nova.printRota();
	do{
		nova = atual.apply2opt(improve2opt);
		nova.incluirPassageiros();
		//cout << "NOVA ROTA" << endl;
		//nova.printRota();
		atualValue = nova.getValue();

		if(atualValue < bestValue){
			//cout << "Melhora para " << atualValue << endl;
			bestValue = atualValue;
			pior = 0;
			atual = nova;
		} else {
			pior++;
		}

		if(pior == 10){
			break;
		} 

	}while(true);
 
	return atual;
}

Instance Instance::localSearchRef(double &bestValue){
	double atualValue, bestLocal;
	int pior = 0;
	incluirPassageiros();

	bestValue = getValue();
	bestLocal = bestValue;

	Instance atual = *this;
	Instance nova = atual;
	Instance melhorLocal = atual;

	bool improve2opt;

	//cout << "Valor Inicial: " << bestValue << endl;
	//nova.printRota();
	int i2, j2;
	do{
		for(int i = 0; i < rota.size() - 4; i++){
			for(int j = i + 2; j < rota.size() - 2; j++){
				nova = atual.__switch(i, j);
				nova.incluirPassageiros();
				atualValue = nova.getValue();
				if(atualValue < bestLocal){
					//cout << "Melhora para " << atualValue << endl;
					bestLocal = atualValue;
					melhorLocal = nova;
				}
			}
		}

		if(bestLocal < bestValue){
			bestValue = bestLocal;
			pior = 0;
			atual = melhorLocal;
		} else {
			pior++;
		}

		if(pior == 10){
			break;
		} 

	}while(true);
 
	return atual;
}

Instance Instance::GRASP(double &bestValue){
	//cout << "INICIEI GRASP " << endl;
	//printRota();
	incluirPassageiros();
	Instance melhor = *this;
	double atualValue;
	bestValue = getValue();
	for(int i = 0; i < 100; i++){
		Instance base;
		base = base.localSearch(atualValue);
		//cout << "GRAPS " << i << "(" << bestValue << ")" << endl;
		if(atualValue < bestValue){
			//cout << " ----- MELHORA GLOBAL: " << bestValue << " => " << atualValue;
			bestValue = atualValue;
			melhor = base;
		}
		//cout << endl;
	}

	return melhor;
}

Instance Instance::GRASPRef(double &bestValue){
	//cout << "INICIEI GRASPREF" << endl << endl;
	//printRota();
	incluirPassageiros();
	Instance melhor = *this;
	double atualValue;
	bestValue = getValue();
	for(int i = 0; i < 100; i++){
		Instance base;
		base = base.localSearchRef(atualValue);
		//cout << "GRAPS " << i << "(" << bestValue << ")" << endl;
		if(atualValue < bestValue){
			//cout << " ----- MELHORA GLOBAL: " << bestValue << " => " << atualValue;
			bestValue = atualValue;
			melhor = base;
		}
		//cout << endl;
	}

	return melhor;
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
	
/* 	for(int i = 0; i < numPass; i++) {
		cout << candidatos[i] << " ";
	} */
	
	return candidatos;
}

double Instance::incluirPassageiros(int index) {
	double soma = 0;
	bool * candidatos = darwin();
	vector<Passageiro> carro;
	for(; index < rota.size(); index++){
		carro.clear();
		soma = 0;
		if(incluirPassageiros(candidatos, index, carro, soma)){
			break;
		}
		rota[index].reset();
	}
	
	delete [] candidatos;

	return soma;
}

bool Instance::incluirPassageiros(bool * candidatos, int index, vector<Passageiro> & carro, double &soma) {
	double custo = 0;
	if(index == rota.size()) {
		return true;
	}

	rota[index].reset();
	if(index != 0){
		custo = (custoArestas[rota[index - 1].getId()][rota[index].getId()].first);
		if(carro.size() == lotacao){
			custo *= (1 - (custoArestas[rota[index - 1].getId()][rota[index].getId()].second));
		}
		if(carro.size() > 0){
			custo /= carro.size();
		}
	}

	soma += custo;


	for(int i = carro.size() - 1; i >= 0; i--) {
		carro[i].setTarifa(carro[i].getTarifa() - custo);
		if(carro[i].getTarifa() < 0) {
			soma = 0;
			return false;
		}
		if(carro[i].getDesembarque() == rota[index].getId()) {
			carro.erase(carro.begin() + i);
			rota[index].saiPass();
		}
	}

	if (candidatos[rota[index].getPassageiro()] && carro.size() < lotacao) {
		rota[index].pegaPassageiro();
		carro.push_back(passageiros[rota[index].getPassageiro()]);
	}
	return incluirPassageiros(candidatos, index+1, carro, soma);
	
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

double Instance::getValue(){
	double soma = 0;
	double custo = 0;
	vector<Passageiro> carro;
	if(rota[0].embarcou()){
		carro.push_back(passageiros[rota[0].getPassageiro()]);
	}

	for(int index = 1; index < rota.size(); index++){
		custo = (custoArestas[rota[index - 1].getId()][rota[index].getId()].first);
		if(carro.size() == lotacao){
			custo *= (1 - custoArestas[rota[index - 1].getId()][rota[index].getId()].second);
		}

		if(carro.size() != 0){
			custo /= carro.size();
		}

		soma += custo;
		for(int i = carro.size() - 1; i >= 0; i--) {
			carro[i].setTarifa(carro[i].getTarifa() - custo);
			if(carro[i].getDesembarque() == rota[index].getId()) {
				carro.erase(carro.begin() + i);
			}
		}
		if (rota[index].embarcou()) {
			carro.push_back(passageiros[rota[index].getPassageiro()]);
		}
	}

	return soma;
}

double Instance::printRotaEmbarques(vector<Passageiro> &historico){
	double soma = 0;
	double custo = 0;
	vector<Passageiro> carro;
	cout << "----------------------------------------------" << endl;
	cout << "FOI PARA CIDADE " << rota[0].getId() << endl;
	cout << "    Tamanho do carro: " << carro.size() << endl;
	cout << "    Todos pagaram: " << custo << endl;
	cout << "    DESEMBARQUES:" << endl;
	cout << "    EMBARQUES:" << endl; 
	if(rota[0].embarcou()){
		cout << "        Passageiro: " << rota[0].getPassageiro() + 1 << " entrou." << endl;
		carro.push_back(passageiros[rota[0].getPassageiro()]);
	}

	for(int index = 1; index < rota.size(); index++){
		custo = (custoArestas[rota[index - 1].getId()][rota[index].getId()].first);
		cout << "----------------------------------------------" << endl;
		cout << "FOI PARA CIDADE " << rota[index].getId() << endl;
		cout << "    Tamanho do carro: " << carro.size() << endl;
		if(carro.size() != 0){
			custo /= carro.size();
		}
		cout << "    Todos pagaram: " << custo << endl;
		soma += custo;
		cout << "    DESEMBARQUES:" << endl;
		for(int i = carro.size() - 1; i >= 0; i--) {
			carro[i].setTarifa(carro[i].getTarifa() - custo);
			if(carro[i].getDesembarque() == rota[index].getId()) {
				cout << "        " << carro[i].getId() << " saiu." << endl;
				historico.push_back(carro[i]);
				carro.erase(carro.begin() + i);
			}
		}
		cout << "    EMBARQUES:" << endl;
		if (rota[index].embarcou()) {
			cout << "        Passageiro: " << rota[index].getPassageiro() + 1 << " entrou." << endl; 
			carro.push_back(passageiros[rota[index].getPassageiro()]);
		}
	}

	soma += custoArestas[rota[rota.size() - 1].getId()][0].first;

	return soma;
}
