#pragma once

#include <iostream>
#include <vector>
#include <map>
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
    std::string lire_str();
    int lire_int(int borneInf, int borneSupp);

    // Attributs
    int nbJoueurs; 
    vector<string> pseudos;
    map<Extensions, bool> extensions;
    InterfaceTerminal interface;



    
public:
    static Controleur* getControleur();
    static void libererJeu();


};
