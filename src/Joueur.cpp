#include "../headers/Joueur.h"
#include "../headers/Monument.h"
#include "../headers/Batiment.h"
#include "../headers/enums.h"

Joueur::Joueur(std::string psdo, TypeJoueur typ) : type(typ), pseudo(psdo), pieces(3), rejoueTour(false), constructions(){
    monuments = {Monument("Gare",4), Monument("Centre commercial",10), Monument("Parc d'atractions",16), Monument("Tour radio",22)};
}

bool Joueur::hasGare() const {
    return monuments[0].getConstruit();
}

bool Joueur::hasTourRadio() const {
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

bool Joueur::hasParcAttractions() const{
    return monuments[2].getConstruit();
}
bool Joueur::hasAeroport() const{
    //to do
    return false;

}
void Joueur::activerCartesBleues(int nbDes) {
    for (auto it = constructions.begin(); it != constructions.end(); it++){
        bool bonNombreAuDe = false;
        for (auto it2 = (*it)->getCombinaisons().begin(); it2 != (*it)->getCombinaisons().end(); it2++) if (*it2 == nbDes) { bonNombreAuDe = true;}
        if ((*it)->getCouleur()==Couleur::bleu && bonNombreAuDe) (*it)->activer();
    }
}

void Joueur::activerCartesVertes(int nbDes) {
    for (auto it = constructions.begin(); it != constructions.end(); it++){
        bool bonNombreAuDe = false;
        for (auto it2 = (*it)->getCombinaisons().begin(); it2 != (*it)->getCombinaisons().end(); it2++) if (*it2 == nbDes) { bonNombreAuDe = true;}
        if ((*it)->getCouleur()==Couleur::vert && bonNombreAuDe) (*it)->activer();
    }
}

void Joueur::activerCartesRouges(int nbDes) {
    for (auto it = constructions.begin(); it != constructions.end(); it++){
        bool bonNombreAuDe = false;
        for (auto it2 = (*it)->getCombinaisons().begin(); it2 != (*it)->getCombinaisons().end(); it2++) if (*it2 == nbDes) { bonNombreAuDe = true;}
        if ((*it)->getCouleur()==Couleur::rouge && bonNombreAuDe) (*it)->activer();
    }
}

void Joueur::activerCartesViolettes(int nbDes){
    for (auto it = constructions.begin(); it != constructions.end(); it++){
        bool bonNombreAuDe = false;
        for (auto it2 = (*it)->getCombinaisons().begin(); it2 != (*it)->getCombinaisons().end(); it2++) if (*it2 == nbDes) { bonNombreAuDe = true;}
        if ((*it)->getCouleur()==Couleur::violet && bonNombreAuDe) (*it)->activer();
    }
}

void Joueur::gagnerPieces() {
    pieces+=2;
}
