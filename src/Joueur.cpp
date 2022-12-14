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


