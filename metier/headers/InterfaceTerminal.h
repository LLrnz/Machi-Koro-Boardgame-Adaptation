#pragma once
#include "../../gui/headers/windowjeu.h"
#include "../headers/Jeu.h"
#include <QLabel>

class InterfaceTerminal
{
    QLabel *ostream;


public:
    InterfaceTerminal();
//    InterfaceTerminal(WindowJeu &ui);
    void setLabel(QLabel *l);
    void afficher(std::string f) const;
    void afficher(int i) const ;
    void afficher(vector<Joueur*> joueurs);
    void afficher(vector<Batiment*> batiments);
    void afficher(vector<Monument*> monuments);
    void afficher(vector<Carte*> cartes);
    std::string lire() const;
    int lire_int();
    int lire_int(int x, int y);
    Joueur* selection_joueur(vector<Joueur*> joueurs);
    Batiment* selection_batiment(vector<Batiment*> batiments);
    Carte* selection_carte(vector<Carte*> cartes);
    Joueur* selection_joueur_batiment(vector<Joueur*> joueurs);
    Monument* selection_monument(vector<Monument*> monuments);
    void changerCouleur(char couleur_texte, char couleur_fond = '0');

};
