#include "Cidade.hpp"

Cidade::Cidade () {
	desembarques = new vector<int>();
	entrou = false;
	passageiro = -1;
}

int Cidade::getPassageiro() {
	return passageiro;
}

void Cidade::setPassageiro(int passageiro) {
	this.passageiro = passageiro;
}

void Cidade::pegaPassageiro(int passageiro) {
	this.entrou = true;
}