#pragma once

#include "CarteRouge.h"
using namespace std;

class BarASushi : public CarteRouge
{

private:
    int nbMonuToActivate; // nombre de monument requis pour pouvoir construire le batiment
public:
    void activer(Joueur *joueurProprietaire);
    BarASushi(int id, std::string nom, TypeBatiment type,
               int prix, int gain, std::vector<int> combinaisons,
               Couleur couleur);
};
