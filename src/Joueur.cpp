#include "../headers/Joueur.h"
#include "../headers/Monument.h"
#include "../headers/Batiment.h"
#include "../headers/enums.h"
#include "../headers/CarteRouge.h"
#include "../headers/CarteVerte.h"
#include "../headers/CarteViolette.h"
#include "../headers/CarteBleue.h"

Joueur::Joueur(std::string psdo, TypeJoueur typ) : type(typ), pseudo(psdo), pieces(3), rejoueTour(false), batiments(){
    monuments = {Monument("Port",2), Monument("Gare",4), Monument("Centre commercial",10), Monument("Parc d'atractions",16), Monument("Tour radio",22), Monument("Aeroport",30)};
}

bool Joueur::hasPort() const {
    return monuments[0].getConstruit();
}

bool Joueur::hasGare() const {
    return monuments[1].getConstruit();
}

bool Joueur::hasCentreCommercial() const {
    return monuments[2].getConstruit();
}

bool Joueur::hasParcAttractions() const{
    return monuments[3].getConstruit();
}

bool Joueur::hasTourRadio() const {
    return monuments[4].getConstruit();
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
bool Joueur::hasAeroport() const{
    return monuments[5].getConstruit();
}


void Joueur::activerCartesBleues(int nbDes){
    for (auto it = batiments.begin(); it != batiments.end(); it++){
        bool bonNombreAuDe = false;
        for (auto it2 = (*it)->getCombinaisons().begin(); it2 != (*it)->getCombinaisons().end(); it2++)
            if (*it2 == nbDes) { bonNombreAuDe = true;}
        if ((*it)->getCouleur()==Couleur::Bleu && bonNombreAuDe){
            dynamic_cast<CarteBleue*>(*it)->activer(*this);
        }
    }
}

void Joueur::activerCartesVertes(int nbDes){
    for (auto it = batiments.begin(); it != batiments.end(); it++){
        bool bonNombreAuDe = false;
        for (auto it2 = (*it)->getCombinaisons().begin(); it2 != (*it)->getCombinaisons().end(); it2++)
            if (*it2 == nbDes) { bonNombreAuDe = true;}
        if ((*it)->getCouleur()==Couleur::Vert && bonNombreAuDe){
            dynamic_cast<CarteVerte*>(*it)->activer(*this);
        }
    }
}

void Joueur::activerCartesRouges(int nbDes){
    for (auto it = batiments.begin(); it != batiments.end(); it++){
        bool bonNombreAuDe = false;
        for (auto it2 = (*it)->getCombinaisons().begin(); it2 != (*it)->getCombinaisons().end(); it2++)
            if (*it2 == nbDes) { bonNombreAuDe = true;}
        if ((*it)->getCouleur()==Couleur::Rouge && bonNombreAuDe){
            dynamic_cast<CarteRouge*>(*it)->activer(*this);
        }
    }
}

void Joueur::activerCartesViolettes(int nbDes){
    for (auto it = batiments.begin(); it != batiments.end(); it++){
        bool bonNombreAuDe = false;
        for (auto it2 = (*it)->getCombinaisons().begin(); it2 != (*it)->getCombinaisons().end(); it2++)
            if (*it2 == nbDes) { bonNombreAuDe = true;}
        if ((*it)->getCouleur()==Couleur::Violet && bonNombreAuDe)
            dynamic_cast<CarteViolette*>(*it)->activer(*this);
    }
}

void Joueur::gagnerPieces(int montant) {
    pieces += montant;
}
