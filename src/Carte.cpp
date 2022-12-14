#include "../headers/Carte.h"

Carte::Carte(int i, std::string n, int p) : id(i),nom(n),prix(p) {
    
}

Carte::~Carte() {

}

//accessors
int Carte::getId() const {
    return id;
}

std::string Carte::getNom() const {
    return nom;
}

TypeBatiment Carte::getType() const {
    return type;
}

int Carte::getPrix() const {
    return prix;
}

std::ostream& Carte::toString() const {
    std::cout << "Carte " << nom << " de type " << " et de prix " << prix << std::endl;
    return std::cout;
}