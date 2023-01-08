#pragma once

#include "CarteViolette.h"
#include "../enums.h"


using namespace std;

class MaisonEdition : public CarteViolette
{
public:
    void activer(Joueur *joueurProprietaire);
    MaisonEdition(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur);
};
