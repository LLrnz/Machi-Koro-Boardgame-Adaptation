#pragma once

#include <iostream>
#include <vector>
#include <map>
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
    Jeu(const Jeu&) = delete;
    Jeu& operator=(const Jeu&) = delete;

    //Attribus
    vector<Batiment*> cartesEnJeu;

    std::vector<Joueur> joueurs;
    int joueurActif;
    Marche* marche;
    bool partieTerminee = false;
    Controleur* controleur; //accès rapide vers le singleton

    // Méthode pour l'initialisation du jeu
    void initialiserCartes(map<Extensions, bool> extensions);
    void initialiserJoueurs(map<std::string, TypeJoueur> listeJoueurs);
    // Méthode pour un tour de jeu
    int lancerDes();
    int jetDes();
    void activerCartesBleues(int nbDes);
    void activerCartesVertes(int nbDes);
    void activerCartesRouges(int nbDes);
    void activerCartesViolettes(int nbDes);
    void extracted(Joueur &joueur, int &i,
                   vector<Monument *> &monumentsAchetables,
                   std::stringstream &s);
    void achat();
    bool verifierVictoire();   
public:
    static Jeu* getJeu();
    static void libererJeu();
    void afficherCartes();


    void genererPartie(map<std::string, TypeJoueur> listeJoueurs, map<Extensions, bool> extensions);
    void boucleDeJeu();
    void tourDeJeu();
    void joueurSuivant();
    void setJoueurActif(int i) { joueurActif = i; };
    bool getPartieTerminee() const { return partieTerminee; };
    int getIndiceJoueurActif() const { return joueurActif; };
    Joueur& getJoueurActif() { return joueurs[joueurActif]; };
    vector<Joueur> getJoueurs() const { return joueurs; };

};
