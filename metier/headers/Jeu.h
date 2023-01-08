#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "../headers/Marche.h"
//#include "../headers/controleur.h"


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
    vector<Joueur>::iterator joueurActif;
    Marche* marche;
    bool partieTerminee = false;
    int conditionVictoire;
    bool deRelances;
    bool deLance;

    // Méthode pour l'initialisation du jeu
    void initialiserCartes(map<Extensions, bool> extensions);
    void initialiserJoueurs(map<std::string, TypeJoueur> listeJoueurs);
    // Méthode pour un tour de jeu
    void lancerDes(int resultatJet);
    void afficherDes(int resultatJet);
    void activerCartesBleues(int nbDes);
    void activerCartesVertes(int nbDes);
    void activerCartesRouges(int nbDes);
    void activerCartesViolettes(int nbDes);
    void extracted(Joueur &joueur, int &i,
                   vector<Monument *> &monumentsAchetables,
                   std::stringstream &s);

    bool verifierVictoire();   
    void donnerCarteDeBase();
public:
    static Jeu& getJeu();
    static void libererJeu();
    void afficherCartes();
    void toucherRSA();
    bool achat(Carte* c);
    void genererPartie(map<std::string, TypeJoueur> listeJoueurs, map<Extensions, bool> extensions);
    void boucleDeJeu();
    bool finDeTour();
    void joueurSuivant();
    //void setJoueurActif(int i) { joueurActif = i; };
    bool getPartieTerminee() const { return partieTerminee; };
    Joueur* getJoueurActif() const { return joueurActif.base(); };
    vector<Joueur> getJoueurs() const { return joueurs; };
    Marche* getMarche() const {return marche;};
    vector<Joueur*> getJoueursSansActifPtr();
    int lancer1de();
    int lancer2des();
    int getNbJoueurs() const;
    void setDesRelances(bool val);
    bool getDesRelances(){return this->deRelances;};
    void activerCartes(int resultatJet);
    bool getDeLance(){return this->deLance;};
    void setDeLance(bool val){this->deLance = val;};

};

