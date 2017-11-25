#include "Passageiro.hpp"

Passageiro::Passageiro() {

}

Passageiro::Passageiro(double tarifa, int embarque, int desembarque) {
	this.tarifa = tarifa;
	this.embarque = embarque;
	this.desembarque = desembarque;
}

double getTarifa() {
	return tarifa;
}

void setTarifa(double tarifa) {
	this.tarifa = tarifa;
}

int getEmbarque() {
	return embarque;
}

int setEmbarque(int embarque) {
	this.embarque = embarque;
}

int getDesembarque() {
	return embarque;
}

int setDesembarque(int desembarque) {
	this.desembarque = desembarque;
}