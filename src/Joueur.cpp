#include "../headers/Joueur.h"
#include "headers/CarteBleue.h"
#include "headers/Monument.h"
#include "headers/Batiment.h"

Joueur::Joueur(std::string psdo, TypeJoueur typ) : type(typ), pseudo(psdo), pieces(3), rejoueTour(false), constructions(){
    monuments = {Monument("Gare"), Monument("Centre commercial"), Monument("Parc d'atractions"), Monument("Tour radio")};
}

bool Joueur::hasDoubleDes() const {
    return monuments[0].getConstruit();
}

bool Joueur::hasRelancerDes() const {
    return monuments[3].getConstruit();
    return false;
}

// va falloir se décider
bool Joueur::hasPort() const {
    // TO DO
    return false;
}

bool Joueur::hasDoubleProduction() const {
    //TO DO
    return false;
}

bool Joueur::hasRejouerDouble() const{
    return monuments[2].getConstruit();
}
bool Joueur::hasAeroport() const{
    //to do
    return false;

}
void Joueur::activerCartesBleues(int nbDes) {
    for (auto it = constructions.begin(); it != constructions.end(); it++){
        //bool bonNombreAuDe = false;
        //for (auto it2 = *it.getCombinaisons().begin(); it2 != *it.getCombinaisons().end(); it2++) if (it2 == nbDes) { bonNombreAuDe = true;}
        //if (*it.getType()==CarteBleue && bonNombreAuDe) *it.activer();
    }
}

void Joueur::activerCartesVertes(int nbDes) {
    //to do
}

void Joueur::activerCartesRouges(int nbDes) {
    //to do
}

void Joueur::activerCartesViolettes(int nbDes){
    //to do
}

void Joueur::gagnerPieces() {
    pieces+=2;
}
