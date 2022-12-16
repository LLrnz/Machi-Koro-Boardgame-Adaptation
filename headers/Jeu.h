#pragma once

#include <iostream>
#include <vector>
#include "../headers/Carte.h"
#include "../headers/Joueur.h"
#include "../headers/Marche.h"

class Jeu
{
    //Singleton
    static Jeu* jeu;
    Jeu();
    ~Jeu();
    Jeu(const Jeu&) = delete;
    Jeu& operator=(const Jeu&) = delete;
    //Attribus
    std::vector<Carte*> cartesEnJeu;
    std::vector<Joueur> joueurs;
    int joueurActif;
    //Marche marche;
    bool partieTerminee = false;

    //Méthode pour l'initialisation du jeu
    void genererPartie();
    void initialiserCartes();
    void initialiserJoueurs();
    //Méthode pour un tour de jeu
    void boucleDeJeu();
    void joueurSuivant();
    void tourDeJeu();
    int lancerDes();
    int jetDes();
    void activerCartesBleues(int nbDes);
    void activerCartesVertes(int nbDes);
    void activerCartesRouges(int nbDes);
    void activerCartesViolettes(int nbDes);
    void achat();
    bool verifierVictoire();   
public:
    static Jeu& getJeu();
    static void libererJeu();
    void afficherCartes();
    
    //Fonctions de service
    bool getPartieTerminee() const { return partieTerminee; };
    int getIndiceJoueurActif() const { return joueurActif; };
    Joueur getJoueurActif() const { return joueurs[joueurActif]; };
    vector<Joueur> getJoueurs() const { return joueurs; };

};
