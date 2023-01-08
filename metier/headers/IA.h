#pragma once
#ifndef IA_H
#define IA_H
#include "../../metier/headers/Joueur.h"
#endif // IA_H
class IA: public Joueur{
    public :
    IA(std::string pseudo) : Joueur(pseudo, TypeJoueur::IA){}
    virtual ~IA();
    virtual int choixDes() = 0;
    virtual Carte* choixAchat(vector<Carte*> cartes) = 0;
    virtual Joueur* choixJoueur(vector<Joueur*> joueurs) = 0;
    virtual Batiment* choixBatiment(vector<Batiment*> batiments) = 0;
    virtual int choixPort() = 0;
    virtual bool choixRelance() = 0;
};
