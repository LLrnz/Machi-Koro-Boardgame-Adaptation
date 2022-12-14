#include "../headers/InterfaceTerminal.h"
#include <string>
#include <iostream>

void InterfaceTerminal::afficher(std::string message) const {
    std::cout << message;
}

void InterfaceTerminal::afficher(int i) const {
    std::cout << i;
}

std::string InterfaceTerminal::lire() const {
    std::string reponse;
    std::cin >> reponse;
    return reponse;
}
