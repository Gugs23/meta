#include "Dupla.hpp"

Dupla::Dupla(int cid, double ccusto) : id(cid), custo(ccusto){

}

bool Dupla::operator < (const Dupla &base) const{
    return custo < base.custo;
}