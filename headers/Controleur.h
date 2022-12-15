#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Jeu.h"
#include "InterfaceTerminal.h"
#include "../headers/InterfaceTerminal.h"
#include "../headers/enums.h"
using namespace std;


class Controleur
{
    // Singleton
    static Controleur* controleur_;
    Controleur();
    ~Controleur();
    Controleur(const Controleur&)=delete;
    Controleur& operator=(const Controleur&)=delete;




    // Attributs
    int nbJoueurs; 
    vector<string> pseudos;
    map<Extensions, bool> extensions;
    InterfaceTerminal interface;
    vector<TypeJoueur> typeJoueurs;



    
public:
    static Controleur* getControleur();
    static void libererJeu();
    static void libererControleur();
    void nouvellePartie();


    // Fonctions de service

    int getNbJoueurs() const { return nbJoueurs; };
    string getPseudo(int i) { return pseudos[i]; };
    TypeJoueur getTypeJoueur(int i) { return typeJoueurs[i]; };
    void demarrer();
    void afficher(std::string f) const;
    std::string lire_str();
    int lire_int(int borneInf, int borneSupp);
};
