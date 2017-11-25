#include "Cidade.hpp"

Cidade::Cidade (int cid) {
	id = cid;
	entrou = false;
	passageiro = -1;
}

int Cidade::getId() {
	return id;
}

void Cidade::setId(int id) {
	this->id = id;
}

int Cidade::getPassageiro() {
	return passageiro;
}

void Cidade::setPassageiro(int passageiro) {
	this->passageiro = passageiro;
}

void Cidade::pegaPassageiro() {
	this->entrou = true;
}