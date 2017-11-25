#ifndef _META_DUPLA_H
#define _META_DUPLA_H


class Dupla{
    public:
    
        int id;

        double custo;

        int index;

        bool operator < (const Dupla &) const;

        Dupla(int = -1, double = 0, int = -1);

    private:
    
};

#endif