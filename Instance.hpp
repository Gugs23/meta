#ifndef _META_INSTANCE_H
#define _META_INSTANCE_H

#include <string>
using std::string;

class MetaParser;

class Instance{

    friend class MetaParser;

    public:
        
        Instance();



    private:

        static int vertices;

        static int passageiros;

        static int capacidade;

        static int edgeDesc;

        static string instanceName;

};

#endif