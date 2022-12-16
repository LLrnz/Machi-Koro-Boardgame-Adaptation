#pragma once
#include <iostream>
#include <vector>
#include "Carte.h"
#include "Batiment.h"
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
    void retirerCarteAchetee(Batiment* c);
    
public: 
    Marche(vector<Batiment*> cartes);
    ~Marche()=default;
    
    void distribuer();
    vector<Batiment*> getCarteDispAchat() const;
    Batiment* acheter(int achat);
}; 
