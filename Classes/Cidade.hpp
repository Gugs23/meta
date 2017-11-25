#ifndef CIDADE_H
#define CIDADE_H

#include <vector>

class Cidade {

	private:
		int id
		vector<int> desembarques;
		bool entrou;
		int passageiro;
	
	public:
		Cidade();
		int getId();
		void setId(int);
		int getPassageiro();
		void setPassageiro(int);
		void pegaPassageiro();
};

#endif