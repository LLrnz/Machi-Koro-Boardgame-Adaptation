#pragma once
#include <iostream>
#include <vector>
#include "Carte.h"
using namespace std;

class Marche
{
private:
    // Attributs
    vector<Carte*> enJeu;
    vector<Carte*> pioche;
    int tailleMarche;

    // Méthodes
    Carte* piocherUneCarte();  // debug ok
    int getTailleMarche() const;  // debug ok
    void retirerCarteAchetee(Carte* c);  // debug ok
    
public: 
    Marche(vector<Carte*> cartes);  // debug ok
    ~Marche()=default;
    void distribuer();  // debug ok
    vector<Carte*> getCarteDispAchat() const;  // debug ok
    Carte* acheter(int achat);  // debug ok
}; 
