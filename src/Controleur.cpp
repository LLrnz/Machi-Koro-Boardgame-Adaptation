#include "../headers/Controleur.h"

Controleur* Controleur::getControleur(){
    if(!Controleur::controleur){
        Controleur::controleur = new Controleur();
    }
    return Controleur::controleur;
}

void Controleur::afficher(std::string f) const{
    this->interface.afficher(f);
}

std::string Controleur::lire(){
    return this->interface.lire();
}

void Controleur::nouvellePartie(){

}
