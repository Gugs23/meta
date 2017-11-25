#include <iostream>
using namespace std;

#include "Instance.hpp"

#include "Parser.hpp"

int main(){
    string name = "../instancias/pcv_cal-50-classe_10-instancia_21.txt";
    Instance inicio = MetaParser::getInstance(name);

    Instance::printBase();
    return 0;
}