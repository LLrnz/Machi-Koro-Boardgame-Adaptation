#pragma once
#ifndef IA_H
#define IA_H
#include "../../metier/headers/Joueur.h"
#endif // IA_H
class Humain: public Joueur{
    public :
    Humain(std::string pseudo) : Joueur(pseudo, TypeJoueur::humain){}
    ~Humain();
};
