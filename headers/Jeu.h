#pragma once

#include <iostream>
#include <vector>
#include "Carte.h"
#include "Controleur.h"
#include "marche.h"

class Joueur;
// class Carte;

class Jeu
{
    //Singleton
    static Jeu* jeu;
    Jeu();
    ~Jeu();
    Jeu(const Jeu&)=delete;
    Jeu& operator=(const Jeu&)=delete;
    //Attribus
    std::vector<Joueur> joueurs;
    int joueurActif;
    std::vector<Carte> cartesEnJeu;
    Marche marche;
    bool partieTerminee = false;

    //Méthode pour l'initialisation du jeu
    void initialiserCartes();
    void initialiserJoueurs();
    //Méthode pour un tour de jeu
    int lancerDes() const;
    void activerCartesBleues(int nbDes) const; //Voir si il faut un const
    void activerCartesVertes(int nbDes) const;
    void activerCartesRouges(int nbDes) const;
    void activerCartesViolettes(int nbDes) const;
    void achat();
    void tourDeJeu();
public:
    static Jeu& getJeu();
    static void libererJeu();

    void genererPartie();
    void boucleDeJeu();
    void tourDeJeu();
    void joueurSuivant();
    void setJoueurActif(int i) { joueurActif = i; };
    bool getPartieTerminee() const { return partieTerminee; };
    int getJoueurActif() const { return joueurActif; };
    vector<Joueur> getJoueurs() const { return joueurs; };

};
