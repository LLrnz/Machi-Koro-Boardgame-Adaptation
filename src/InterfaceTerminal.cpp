#include "../headers/Controleur.h"
#include "../headers/InterfaceTerminal.h"
#include "string"
#include "iostream"

void InterfaceTerminal::afficher(string message) const {
    std::cout << message;
}

void InterfaceTerminal::afficher(int i) const {
    std::cout << i;
}

string& InterfaceTerminal::lire() const {
    string reponse;
    std::cin >> reponse;
    return reponse;
}