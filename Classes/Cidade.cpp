#include "Cidade.hpp"

Cidade::Cidade (int cid) {
	id = cid;
	entrou = false;
	passageiro = -1;
	sairam = 0;
}

Cidade::Cidade(const Cidade &base){
	id = base.id;
	entrou = base.entrou;
	passageiro = base.passageiro;
	sairam = base.sairam;
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

void Cidade::reset(){
	this->entrou = false;
	this->sairam = 0;
}

void Cidade::saiPass(){
	this->sairam++;
}

int Cidade::getSairam(){
	return this->sairam;
}

bool Cidade::embarcou(){
	return this->entrou;
}
