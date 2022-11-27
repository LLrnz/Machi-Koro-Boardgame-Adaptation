#include "../headers/Carte.h"

Carte::Carte(int i, std::string n, TypeBatiment t, int p) :
    id(i),nom(n),type(t),prix(p) {

}

Carte::~Carte() {

}
