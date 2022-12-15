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


void Controleur::afficher(std::string f) const{
    this->interface.afficher(f);
}

std::string Controleur::lire_str(){
    return this->interface.lire();
}

int Controleur::lire_int(int borneInf, int borneSupp){
    return this->interface.lire_int(borneInf, borneSupp);
}


void Controleur::nouvellePartie(){
    //Set up des parametres de la partie

    //set up joueurs
    //nb joueurs
    this->afficher("Bonjour, combien de joueurs ?");
    this->nbJoueurs = this->lire_int(1, 4);
    //pseudos joueurs
    for(int i = 0; i < this->nbJoueurs; i++){
        this->afficher("Pseudo joueur "+ to_string(i) +" :");
        this->pseudos.push_back(this->lire_str());
    }

    //set up extensions
    for( const auto e : {Extensions::harbour, Extensions::millionaire} ){
        this->afficher("Jouer avec l'extension ?");
        bool val = this->lire_int(0,1);
        this->extensions.emplace(e, val);

    }
    Jeu::getJeu().genererPartie();


}


