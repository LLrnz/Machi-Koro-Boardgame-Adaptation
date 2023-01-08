#pragma once

#include "CarteViolette.h"
#include "../enums.h"


using namespace std;

class CentreImpot : public CarteViolette
{
public:
    void activer(Joueur *joueurProprietaire);
    CentreImpot(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur);
};
