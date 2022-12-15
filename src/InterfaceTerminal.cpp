#include "../headers/InterfaceTerminal.h"

void InterfaceTerminal::afficher(std::string f) const{
    std::cout << f;
}

std::string InterfaceTerminal::lire() const{
    std::string res;
    std::cin >> res;
    return res;
}

int InterfaceTerminal::lire_int(){

    int res = NULL;
    while (res == NULL){
        std::string str = this->lire();

        try {
            res = std::stoi(str);
        } catch (...) {
            std::cout << "Merci d'entrer un chiffre.";
        }
    }
    return res;
}

int InterfaceTerminal::lire_int(int x, int y){
    int res = NULL;
    while(res == NULL){
        res = this->lire_int();
        if(!((res >= x) && (res <= y))){
            res = NULL;
        }
    }
    return res;
}
