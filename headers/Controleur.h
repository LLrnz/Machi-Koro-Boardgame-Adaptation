#pragma once
#include <iostream>
#include <vector>
#include <map>
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
    map<Extensions, bool> extensions;
    InterfaceTerminal interface;

public:
    static Controleur* getControleur();
    static void libererControleur();
    void nouvellePartie();

    // Fonctions de service

    int getNbJoueurs() const { return nbJoueurs; };
    void demarrer();
    void afficher(std::string f) const;
    void afficher(int i) {interface.afficher(i);};
    std::string lire_str();
    int lire_int(int borneInf, int borneSupp);
    map<Extensions, bool> getExtensions() const {return extensions;};
};
