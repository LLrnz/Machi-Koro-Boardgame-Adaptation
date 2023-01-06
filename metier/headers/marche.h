#pragma once
#include <iostream>
#include <vector>
#include "Joueur.h"
using namespace std;

class Marche
{
private:
    // Attributs
    vector<Batiment*> enJeu;
    vector<Batiment*> pioche;
    int tailleMarche;

    // Méthodes
    Batiment* piocherUneCarte();
    int getTailleMarche() const;
    void retirerCarteAchetee(Batiment* b);

    
public: 
    Marche(vector<Batiment*> cartes);
    ~Marche()=default;
    
    void distribuer();
    vector<Batiment*> getCarteDispAchat() const;
    //Batiment* acheter(int achat);

    void acheter(Batiment*);
}; 
