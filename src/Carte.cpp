#include "../headers/Carte.h"

Carte::Carte(int i, std::string n, int p) : id(i),nom(n),prix(p) {
    
}


//accessors
int Carte::getId() const {
    return id;
}

std::string Carte::getNom() const {
    return nom;
}

int Carte::getPrix() const {
    return prix;
}


