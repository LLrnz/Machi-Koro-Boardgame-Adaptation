#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "../headers/Batiment.h"
#include "../headers/Joueur.h"
#include "../headers/marche.h"
#include "../headers/Controleur.h"

using namespace std;

class Jeu
{
    // Singleton
    static Jeu* jeu;

    Jeu();
    ~Jeu();
    vector<Batiment*> cartesEnJeu;

    Jeu(const Jeu&) = delete;
    Jeu& operator=(const Jeu&) = delete;

    // Attributs
    vector<Joueur> joueurs;
    int joueurActif;
    Marche* marche;
    bool partieTerminee = false;
    Controleur* controleur; //accès rapide vers le singleton

    // Méthode pour l'initialisation du jeu
    void initialiserCartes();
    void initialiserJoueurs();
    // Méthode pour un tour de jeu
    int lancerDes();
    void activerCartesBleues(int nbDes) const; // TODO Voir si il faut un const
    void activerCartesVertes(int nbDes) const;
    void activerCartesRouges(int nbDes) const;
    void activerCartesViolettes(int nbDes) const;
    void achat();
    int jetDes();
public:
    static Jeu& getJeu();
    static void libererJeu();
    void afficherCartes();


    void genererPartie();
    void boucleDeJeu();
    void tourDeJeu();
    void joueurSuivant();
    void setJoueurActif(int i) { joueurActif = i; };
    bool getPartieTerminee() const { return partieTerminee; };
    Joueur getJoueurActif() const { return joueurs[joueurActif]; };
    int getIndiceJoueurActif() const { return joueurActif; };
    vector<Joueur> getJoueurs() const { return joueurs; };

};
