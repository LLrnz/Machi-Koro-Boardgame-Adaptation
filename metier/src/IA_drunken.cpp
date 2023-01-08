#include "../headers/IA_drunken.h"
#include "../headers/Controleur.h"//;

IA_drunken::~IA_drunken(){}

int IA_drunken::choixDes(){
    return Controleur::aleat(1,2);
}

Carte* IA_drunken::choixAchat(vector<Carte*> cartes){
    Carte* res = nullptr;
    if(!cartes.empty()){
        res = cartes.at(Controleur::aleat(0,cartes.size()));
    }
    return res;
}

Joueur* IA_drunken::choixJoueur(vector<Joueur*> joueurs){
    Joueur* res = nullptr;
    if(!joueurs.empty()){
        res = joueurs.at(Controleur::aleat(0,joueurs.size()));
    }
    return res;
}

Batiment* IA_drunken::choixBatiment(vector<Batiment*> batiments){
    Batiment* res = nullptr;
    if(!batiments.empty()){
        res = batiments.at(Controleur::aleat(0,batiments.size()));
    }
    return res;
}

int IA_drunken::choixPort(){
    return Controleur::aleat(0,2);
}

bool IA_drunken::choixRelance(){
    return Controleur::aleat(0,1);
}
