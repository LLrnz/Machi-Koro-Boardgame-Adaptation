#pragma once

#include <iostream>
#include <vector>
#include "../headers/Carte.h"
#include "../headers/Joueur.h"

class Jeu
{
    //Singleton
    static Jeu* jeu;

    Jeu();
    ~Jeu();
    std::vector<Carte*> cartesEnJeu;

    Jeu(const Jeu&) = delete;
    Jeu& operator=(const Jeu&) = delete;

    //Attribus
    std::vector<Joueur> joueurs;
    int joueurActif;
    //Marche marche;
    bool partieTerminee = false;

    //Méthode pour l'initialisation du jeu
    void initialiserCartes();
    void initialiserJoueurs();
    //Méthode pour un tour de jeu
    int lancerDes();
    void activerCartesBleues(int nbDes); //Voir si il faut un const
    void activerCartesVertes(int nbDes);
    void activerCartesRouges(int nbDes);
    void activerCartesViolettes(int nbDes);
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
    int getIndiceJoueurActif() const { return joueurActif; };
    Joueur getJoueurActif() const { return joueurs[joueurActif]; };
    vector<Joueur> getJoueurs() const { return joueurs; };

};
