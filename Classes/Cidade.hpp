#ifndef CIDADE_H
#define CIDADE_H

#include <vector>
using std::vector;

class Cidade {

	private:
		int id;
		vector<int> desembarques;
		bool entrou;
		int passageiro;
	
	public:
		Cidade(int = -1);
		int getId();
		void setId(int);
		int getPassageiro();
		void setPassageiro(int);
		void pegaPassageiro();
};

#endif