#include "../headers/Monument.h"


Monument::Monument(std::string n,int p):Carte(0,n,p),construit(false){};



void Monument::acheter(){
    this->setConstruit();
}

Monument::~Monument(){};


std::string Monument::to_string() const{
    return "Ceci est un monment";
}
