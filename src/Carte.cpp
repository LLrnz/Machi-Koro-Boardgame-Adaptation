#include "../headers/Carte.h"

Carte::Carte(int i, std::string n, int p) : id(i),nom(n),prix(p) {}

std::ostream& Carte::toString() const {
    std::cout << "Carte " << nom << " de type " << " et de prix " << prix << std::endl;
    return std::cout;
}
