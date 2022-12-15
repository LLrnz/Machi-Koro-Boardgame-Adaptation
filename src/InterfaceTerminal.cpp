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
    bool chiffre = false;
    int res;
    while (!chiffre){
        std::string str = this->lire();

       try {
            res = std::stoi(str);
            chiffre = true;
       }catch (...) {
            std::cout << "Merci d'entrer un chiffre.";
       }
    }
    return res;
}

int InterfaceTerminal::lire_int(int x, int y){
    bool bornesOk = false;
    int res;
    while(!bornesOk){
        res = this->lire_int();
        if(((res >= x) && (res <= y))){
            bornesOk = true;
        }
    }
    return res;
}
