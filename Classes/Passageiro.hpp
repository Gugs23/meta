#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

class Passageiro {

	private:
		int id;
		double tarifa;
		int embarque;
		int desembarque;
	
	public:
		Passageiro();
		Passageiro(int, double, int, int);
		int getId();
		void setId(int);
		double getTarifa();
		void setTarifa(double);
		int getEmbarque();
		int getDesembarque();
		void setEmbarque(int);
		void setDesembarque(int);
};

#endif