#pragma once

#include "RougeNbBat.h"
#include <vector>
#include <string>
using namespace std;

class ClubPrive : public RougeNbBat
{
public:
    virtual void activer(Joueur *joueurProprietaire);
    ClubPrive(int id, std::string nom, TypeBatiment type,
               int prix, int gain, std::vector<int> combinaisons,
               Couleur couleur, int nbMonuToActivate);
};
