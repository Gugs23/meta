#include "Passageiro.hpp"

Passageiro::Passageiro() {

}

Passageiro::Passageiro(int id, double tarifa, int embarque, int desembarque) {
	this->id = id;
	this->tarifa = tarifa;
	this->embarque = embarque;
	this->desembarque = desembarque;
}

int Passageiro::getId(){
	return id;
}

void Passageiro::setId(int id){
	this->id = id;
}

double Passageiro::getTarifa() {
	return tarifa;
}

void Passageiro::setTarifa(double tarifa) {
	this->tarifa = tarifa;
}

int Passageiro::getEmbarque() {
	return embarque;
}

void Passageiro::setEmbarque(int embarque) {
	this->embarque = embarque;
}

int Passageiro::getDesembarque() {
	return desembarque;
}

void Passageiro::setDesembarque(int desembarque) {
	this->desembarque = desembarque;
}