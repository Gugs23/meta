#ifndef CIDADE_H
#define CIDADE_H

#include <vector>

class Cidade {

	private:
		vector<int> desembarques;
		bool entrou;
		int passageiro;
	
	public:
		Cidade();
		int getPassageiro();
		void setPassageiro(int);
		void pegaPassageiro();
};

#endif