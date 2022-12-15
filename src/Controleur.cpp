#include "../headers/Controleur.h"

Controleur::Controleur() {}
Controleur::~Controleur() {}

Controleur* Controleur::controleur_ = nullptr;
Controleur* Controleur::getControleur() {
    if (controleur_ == nullptr){
        Controleur* controleur_ = new Controleur();
        return controleur_;
    }
    return controleur_;
}

void Controleur::libererControleur() {
    delete controleur_;
    controleur_ = nullptr;
}


void Controleur::afficher(string s) {
	interface.afficher(s);
}
void Controleur::afficher(int i) {
	interface.afficher(i);
}
string Controleur::lire(){
	return interface.lire();
}
