#pragma once

#include <iostream>
#include <vector>

class Carte;

class Marche
{
    //Attributs
    std::vector<Carte> enJeu;
    std::vector<Carte> pioche;
    int tailleMarche;

    //Méthodes
    &Carte piocherUneCarte();
    int getTailleMarche() const;
    void retirerCarteAchetee(Carte& aSup);
    
public:
    void piocher(); //rename en distribuer
    std::vector<Carte> getCarteDispAchat() const;
    Cartes& acheter(int achat);

};

