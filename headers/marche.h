#pragma once
#include <iostream>
#include <vector>
#include "Carte.h"
using namespace std;

class Marche
{
private:
    // Attributs
    vector<Carte&> enJeu;
    vector<Carte&> pioche;
    int tailleMarche;

    // Méthodes
    Carte& piocherUneCarte();
    int getTailleMarche() const;
    void retirerCarteAchetee(Carte& c);
    
public:
    void distribuer();
    vector<Carte> getCarteDispAchat() const;
    Carte& acheter(int achat);

};

