#pragma once

#include <iostream>
#include <vector>
#include "Jeu.h"
using namespace std;


class Controlleur
{
    //Singleton
    static Controlleur* controlleur;
    Controlleur();
    ~Controlleur();
    Controlleur(const Controlleur&)=delete;
    Controlleur& operator=(const Controlleur&)=delete;

    //Attribus
    int nbJoueurs; 
    vector<string> pseudos;
    vector<bool> extensions;
    InterfaceTerminal interface;

    
public:
    static Controlleur& getControlleur();
    static void libererJeu();

    void nouvellePartie();
    void demarrer();
    void afficher(ostream& f) const;
    ostream& lire();

};
