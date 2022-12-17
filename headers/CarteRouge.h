#pragma once

#include "Batiment.h"
#include <vector>
#include <string>
//#include "../headers/Joueur.h"
using namespace std;


class CarteRouge : public Batiment {

private:
    int nbMonuToActivate; // nombre de monument requis pour pouvoir construire le batiment
public:
    virtual void activer(Joueur joueurProprietaire);
    CarteRouge(int id, std::string nom, TypeBatiment type,
                int prix, int gain, std::vector<int> combinaisons,
                Couleur couleur, int nbMonuToActivate);
    int getNbMonuToActivate();
    std::string to_string() const;

};
