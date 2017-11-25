#include "Dupla.hpp"

Dupla::Dupla(int cid, double ccusto, int cindex) : id(cid), custo(ccusto), index(cindex){

}

bool Dupla::operator < (const Dupla &base) const{
    return custo < base.custo;
}