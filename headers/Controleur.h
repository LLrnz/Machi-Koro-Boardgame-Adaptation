#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "../headers/InterfaceTerminal.h"


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
    Joueur* selection_joueur(vector<Joueur*> joueurs);
    Batiment* selection_batiment(vector<Batiment*> batiments);
    void afficher(vector<Joueur*> joueurs);
    void afficher(vector<Batiment*> batiments);
    Joueur* selection_joueur_batiment(vector<Joueur*> joueurs){
        return interface.selection_joueur_batiment(joueurs);

    };

    Carte* selection_carte(vector<Carte*> cartes){
        return interface.selection_carte(cartes);
    }

    Monument* selection_monument(vector<Monument*> monuments){
        return interface.selection_monument(monuments);
    }
};
