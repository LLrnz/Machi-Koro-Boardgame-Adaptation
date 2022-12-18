#include "../headers/Joueur.h"
#include "../headers/enums.h"
#include<bits/stdc++.h>

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
    for (auto &it : batiments){
        bool bonNombreAuDe = false;
        for (auto &it2 : it->getCombinaisons())
            if (it2 == nbDes) { bonNombreAuDe = true;}
        if (it->getCouleur()==Couleur::Bleu && bonNombreAuDe)
             it->activer(this);
    }
}
void Joueur::activerCartesVertes(int nbDes){
    for (auto &it : batiments){
        bool bonNombreAuDe = false;
        for (auto &it2 : it->getCombinaisons() )
            if (it2 == nbDes) { bonNombreAuDe = true;}

        if (it->getCouleur()==Couleur::Vert && bonNombreAuDe)
            it->activer(this);
    }
}


void Joueur::activerCartesRouges(int nbDes){
    for (auto &it : batiments){
        bool bonNombreAuDe = false;
        for (auto &it2 : it->getCombinaisons())
            if (it2 == nbDes) { bonNombreAuDe = true;}
        if (it->getCouleur()==Couleur::Rouge && bonNombreAuDe){
            it->activer(this);
        }
    }
}


void Joueur::activerCartesViolettes(int nbDes){
    for (auto &it : batiments){
        bool bonNombreAuDe = false;
        for (auto &it2 : it->getCombinaisons())
            if (it2 == nbDes) { bonNombreAuDe = true;}
        if (it->getCouleur()==Couleur::Violet && bonNombreAuDe)
            it->activer(this);
    }
}

void Joueur::gagnerPieces(int montant) {
    pieces += montant;
}

int Joueur::getNbMonumentsConstruits(){
    int res = 0;
    for(const auto &m : monuments){
        if(m.getConstruit()){
            res++;
        }
    }
    return res;
}

void Joueur::enleverBatiment(Batiment* batiment){
    auto it = std::find(batiments.begin(), batiments.end(), batiment);
    if (it != batiments.end()) {
        batiments.erase(it);
    }
}

std::string Joueur::to_string(){
    return pseudo + "(" + std::to_string(pieces) + "pièces)";
}

vector<Monument*> Joueur::getMonuments() {
    vector<Monument*> res;
    for(auto &m : monuments){
        Monument* m_ptr = &m;
        res.push_back(m_ptr);
    }
    return res;
}
