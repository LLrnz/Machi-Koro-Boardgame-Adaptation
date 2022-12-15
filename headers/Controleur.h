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

    //vector<TypeJoueur> typeJoueurs;
    //vector<string> pseudos; inutiles car utilisation de map joueurs

    map<Extensions, bool> extensions;
    map<std::string, TypeJoueur> joueurs;
    InterfaceTerminal interface;




    
public:
    static Controleur* getControleur();
    static void libererJeu();
    static void libererControleur();
    void nouvellePartie();


    // Fonctions de service

    int getNbJoueurs() const { return nbJoueurs; };

    map<std::string, TypeJoueur> getJoueurs(){
        return joueurs;
    }

//    //[DEPRECIEE] très laid il faut arrêter d'accéder aux pseudos comme ça
//    string getPseudo(int i) {
//        auto it = joueurs.begin();
//        std::advance(it, i);
//        return it->first;
//    };

//    //[DEPRECIEE] très laid il faut arrêter d'accéder aux types comme ça
//    TypeJoueur getTypeJoueur(int i) {
//        auto it = joueurs.begin();
//        std::advance(it, i);
//        return it->second;
//    };

    void demarrer();
    void afficher(std::string f) const;
    std::string lire_str();
    int lire_int(int borneInf, int borneSupp);
};
