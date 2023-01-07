#pragma once

#include "CarteRouge.h"
#include <vector>
#include <string>
using namespace std;

class RougeNbBat : public CarteRouge
{

private:
    int nbMonuToActivate; // nombre de monument requis pour pouvoir construire le batiment
public:
    virtual void activer(Joueur *joueurProprietaire);
    RougeNbBat(int id, std::string nom, TypeBatiment type,
               int prix, int gain, std::vector<int> combinaisons,
               Couleur couleur, int nbMonuToActivate);
    int getNbMonuToActivate() const { return nbMonuToActivate;}
};
