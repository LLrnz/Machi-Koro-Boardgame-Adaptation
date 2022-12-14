#pragma once

#include <iostream>
#include <vector>
#include "Jeu.h"
#include "InterfaceTerminal.h"
using namespace std;


class Controleur
{
    // Singleton
    static Controleur* controleur;
    Controleur();
    ~Controleur();
    Controleur(const Controleur&)=delete;
    Controleur& operator=(const Controleur&)=delete;

    void nouvellePartie();
    void demarrer();
    void afficher(std::string f) const;
    std::string lire();

    // Attributs
    int nbJoueurs; 
    vector<string> pseudos;
    vector<bool> extensions;
    InterfaceTerminal interface;



    
public:
    static Controleur* getControleur();
    static void libererJeu();


};
