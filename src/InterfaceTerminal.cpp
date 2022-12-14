#include "../headers/InterfaceTerminal.h"

void InterfaceTerminal::afficher(std::string f) const{
    std::cout << f;
}

std::string InterfaceTerminal::lire() const{
    std::string res;
    std::cin >> res;
    return res;
}
