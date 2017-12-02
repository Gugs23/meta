#ifndef _META_INSTANCE_H
#define _META_INSTANCE_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::fixed;


#include <algorithm>


#include <iomanip>
using std::setprecision;

#include<vector>
using std::vector;

#include <string>
using std::string;

#include <utility>
using std::pair;
using std::make_pair;

#include "Cidade.hpp"

#include "Passageiro.hpp"

#include "Dupla.hpp"

#define __MIN(A, B) A < B ? A : B

class MetaParser;

class Instance{

    friend class MetaParser;

    public:
        
        Instance();

        Instance apply2opt(bool &);
		
		bool* darwin();
		
		double incluirPassageiros(int = 0);
		
		bool incluirPassageiros(bool*, int, vector<Passageiro> &, double &);

        static void printBase();
        
        void printRota();
		
        void printTripulacao();

        double printRotaEmbarques(vector<Passageiro> &);

        double getValue(bool &);

        double getValue();

        Instance localSearch(double &);

        Instance localSearchRef(double &);

        Instance GRASP(double &);

        Instance GRASPRef(double &);

        Instance removePass(int);

        Instance improvePass(double &);

        Instance incluiPass(int, int, double &, bool *);

        static int getLotacao() { return lotacao; };

        Instance refinaSolucao(double &);

        Instance localSearchPass(double &);

        Instance melhorDoMelhorDoMundo(double &);


    private:

        vector<Cidade> rota;
		
        vector<Passageiro> tripulacao;

        static int vertices;

        static int numPass;

        static int lotacao;

        static int edgeDesc;

        static string instanceName;

        static pair<double, double> ** custoArestas;

        static vector<Cidade> cidades;

        static vector<Passageiro> passageiros;
		
        void reconstruirTripulacao(int, int);

        Instance __switch(int, int);

        Instance __switch(int, int, double &);

        Instance pegaPassageiro(int, double &);

        Instance revert();

        

};

#endif