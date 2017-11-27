#ifndef CIDADE_H
#define CIDADE_H

#include <vector>
using std::vector;

class Cidade {

	private:
		int id;
		bool entrou;
		int passageiro;
		int sairam;
	
	public:
		Cidade(int = -1);
		Cidade(const Cidade &);
		int getId();
		void setId(int);
		int getPassageiro();
		void setPassageiro(int);
		void pegaPassageiro();
		void reset();
		void saiPass();
		int getSairam();
		bool embarcou();
};

#endif