#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

class Passageiro {

	private:
		double tarifa;
		int embarque;
		int desembarque;
	
	public:
		Passageiro();
		Passageiro(double, int, int);
		double getTarifa();
		void setTarifa(double);
		int getEmbarque();
		void setEmbarque(int);
		void setEmbarque(int);
};

#endif