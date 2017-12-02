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
	int mod = vertices / 4;
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

Instance Instance::__switch(int ini, int fim, double &valor){
	vector<Cidade> novaRota;

	valor = valor - custoArestas[rota[ini].getId()][rota[ini + 1].getId()].second -  custoArestas[rota[fim].getId()][rota[fim + 1].getId()].second;
	valor += custoArestas[rota[ini].getId()][rota[fim].getId()].second + custoArestas[rota[ini + 1].getId()][rota[fim + 1].getId()].second;


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

	double valorInterno;

	Instance atual = *this;
	Instance nova = atual;

	bool improve2opt;

	//cout << "Valor Inicial: " << bestValue << endl;
	//nova.printRota();
	do{
		nova = atual.apply2opt(improve2opt);
		nova.incluirPassageiros();

		Instance interna = nova;
		interna = nova.improvePass(valorInterno);
		//cout << "NOVA ROTA" << endl;
		//nova.printRota();
		atualValue = nova.getValue();

		if(valorInterno < atualValue){
			atualValue = valorInterno;
			nova = interna;
		}

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
	double custo;
	vector<Passageiro> carro;
	while(true){
		if(index == rota.size() - 1){//Terminou de incluir passageiros
			break;
		}
		custo = 0;
		pair<double, double> aresta = custoArestas[rota[index].getId()][rota[index + 1].getId()];

		if(index > 0){
			custo = aresta.first;
			if(carro.size() == lotacao){
				custo = custo * (1 - aresta.second);
			}

			if(carro.size() > 0){
				custo = custo / (double)carro.size();
			}
		}

		soma += custo;

		for(int i = carro.size() - 1; i >= 0; i--){
			carro[i].setTarifa(carro[i].getTarifa() - custo);
			if(carro[i].getTarifa() < 0){//Passou limite
				candidatos[carro[i].getId() - 1] = false;//Desconsidera esse passageiro
				carro.clear(); //Limpa o carro
				index = 0;//Reinicia o processo
				soma = 0;
				for(int j = 0; j <= index; j++){
					rota[j].reset();//Limpa rota
				}
			}
		}

		if(candidatos[rota[index].getPassageiro()] && carro.size() < lotacao){
			rota[index].pegaPassageiro();
			carro.push_back(passageiros[rota[index].getPassageiro()]);
		}

		index++;

	}
	
	delete [] candidatos;

	return soma;
}

Instance Instance::improvePass(double &bestValue){
	double valor;
	bestValue = getValue();
	Instance melhor = *this;
	for(int i = 0; i < rota.size() - 1; i++){
		int lim = passageiros[rota[i].getPassageiro()].getDesembarque();
		Instance atual = removePass(i);
		for(int j = 0; j <= lim; j++){
			Instance nova = atual.pegaPassageiro(j, valor);
			if(valor > 0 && valor < bestValue){
				melhor = nova;
				bestValue = valor;
			}
		}
	}

	return melhor;
}

Instance Instance::localSearchPass(double &bestValue){
	bestValue = getValue();
	Instance melhor = *this;
	double valorAtual;

	int erros = 0;

	while(true){
		Instance nova = melhor.improvePass(valorAtual);

		if(valorAtual > 0 && valorAtual < bestValue){
			erros = 0;
			bestValue = valorAtual;
			melhor = nova;
		} else {
			erros++;
		}

		if(erros == 20){
			break;
		}
	}

	return melhor;
}

bool compara(const pair<Instance, double> &a, const pair<Instance, double> &b){
	return a.second < b.second;
}

Instance Instance::melhorDoMelhorDoMundo(double &valor){
	Instance base;
	Instance complemento = base.revert();
 	double valor1, valor2;
	Instance comp1 = base.refinaSolucao(valor1);
	Instance comp2 = complemento.refinaSolucao(valor2);

	//cout << valor1 << " " << valor2 << endl;
	if(valor1 < valor2){
		valor = valor1;
		return comp1;
	} else {
		valor = valor2;
		return comp2;
	}

	return base;
}

Instance Instance::revert(){
	Instance nova = *this;
	for(int i = 0; i < rota.size(); i++){
		nova.rota[rota.size() - 1 - i] = rota[i];
	}
	return nova;
}

Instance Instance::refinaSolucao(double &valor){
	vector<pair<Instance, double> > melhores_rotas;
	valor = getValue();
	double atualValue;
	for(int i = 0; i < rota.size() - 4; i++){
		for(int j = i + 2; j < rota.size() - 2; j++){
			atualValue = valor;
			Instance nova = __switch(i, j, atualValue);
			melhores_rotas.push_back(make_pair(nova, atualValue));
		}
	}

	sort(melhores_rotas.begin(), melhores_rotas.end(), compara);
	
	int dim = melhores_rotas.size() % 10;

	int melhor = -1;

	double novoValor;


	for(int i = 0; i < dim; i++){
		melhores_rotas[i].first.incluirPassageiros();
		melhores_rotas[i].first = melhores_rotas[i].first.localSearchPass(novoValor);
		if(novoValor < valor){
			valor = novoValor;
			melhor = i;
		}
	}

	if(melhor == -1){
		return *this;
	}

	return melhores_rotas[melhor].first;

}

Instance Instance::pegaPassageiro(int idRota, double &valor){
	Instance nova = *this;
	bool viavel;
	nova.rota[idRota].pegaPassageiro();
	valor = nova.getValue(viavel);
	if(!viavel){
		valor = -1;
		return *this;
	}
	return nova;
}

Instance Instance::removePass(int idRota){
	Instance nova = *this;
	nova.rota[idRota].reset();
	return nova;
}

Instance Instance::incluiPass(int in, int out, double &bestValue, bool * possiveis){
	Instance melhor = *this;
	Instance atual = melhor;
	bool viavel;
	double valorAtual;
	bestValue = melhor.getValue();
	for(int i = 0; i < out; i++){
		if(possiveis[rota[i].getPassageiro()] && !rota[i].embarcou()){
			atual = *this;
			atual.rota[i].pegaPassageiro();
			valorAtual = atual.getValue(viavel);
			if(viavel && valorAtual < bestValue){
				bestValue = valorAtual;
				melhor = atual;
			}
		}
	}

	return melhor;
}

/* bool Instance::incluirPassageiros(bool * candidatos, int index, vector<Passageiro> & carro, double &soma) {
	double custo = 0;
	bool passou = true;
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
			candidatos[rota[index].getPassageiro()] = false;
			passou = false;
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
	if(!passou){
		return false;
	}
	return incluirPassageiros(candidatos, index+1, carro, soma);
	
} */

bool Instance::incluirPassageiros(bool * candidatos, int index, vector<Passageiro> & carro, double &soma) {
	double custo = 0;
	while(index < rota.size()){
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
				candidatos[carro[i].getId() - 1] = false;
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
		index++;
	}
	return true;
	
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

double Instance::getValue(bool &viavel){
	viavel = true;
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
		} else if (carro.size() > lotacao){
			viavel = false;
			return -1;
		}

		if(carro.size() != 0){
			custo /= carro.size();
		}

		soma += custo;
		for(int i = carro.size() - 1; i >= 0; i--) {
			carro[i].setTarifa(carro[i].getTarifa() - custo);
			if(carro[i].getTarifa() < 0){
				viavel = false;
				return -1;
			}
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
