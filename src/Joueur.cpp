#include "../headers/Joueur.h"

Joueur::Joueur(std::string psdo, TypeJoueur typ) : type(typ), pseudo(psdo){

}

bool Joueur::hasDoubleDes() const {
    // TO DO
    return false;
}

bool Joueur::hasRelancerDes() const {
    // TO DO
    return false;
}

// va falloir se décider
bool Joueur::hasPort() const {
    // TO DO
    return false;
}


int Joueur::perdrePieces(int nb){
// Soustrait le nombre nb de pièces au joueur et retourne le nombre de pièces 
// réellement soustraites (un joueur ne peut pas avoir un nombre négatif de pièces).

    if (pieces - nb < 0){ // si le joueur doit perdre plus d'argent qu'il n'en a
        int tmp = pieces;
        pieces = 0;    // ben il est fauché
        return tmp; // et on retourne ce qu'il avait (=ce qu'il a perdu)
    }

    pieces -= nb; // sinon, on diminue son solde 
    return nb; // et on retourne ce qu'il a perdu
};

