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
    int joueursActif;


    //Marche marche;                c'est quoi ça ?

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
    bool verifierVictoire();
public:
    static Jeu& getJeu();
    static void libererJeu();
    void afficherCartes();


    void genererPartie();
    void boucledeJeu();
    void joueurSuivant();

};
