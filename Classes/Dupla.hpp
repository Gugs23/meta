#ifndef _META_DUPLA_H
#define _META_DUPLA_H


class Dupla{
    public:
    
        int id;

        double custo;

        bool operator < (const Dupla &);

        Dupla(int = -1, double = 0);

    private:
    
};

#endif