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

    // Attributs
    int nbJoueurs; 
    vector<string> pseudos;
    vector<bool> extensions;
    InterfaceTerminal interface;
    vector<TypeJoueur> typeJoueurs;

    
public:
    static Controleur& getControleur();
    static void libererControleur();

    void nouvellePartie();
    void demarrer();
    void afficher(string s);
    void afficher(int i);
    string& lire();

    // Fonctions de service

    int getNbJoueurs() const { return nbJoueurs; };
    string getPseudo(int i) { return pseudos[i]; };
    TypeJoueur getTypeJoueur(int i) { return typeJoueurs[i]; };
};
