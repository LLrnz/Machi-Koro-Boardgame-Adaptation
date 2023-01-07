#pragma once

#include "CarteVerte.h"
#include <vector>
#include <string>
using namespace std;

class EntrepriseDemenage : public CarteVerte
{
public:
    void activer(Joueur *joueurProprietaire);
    EntrepriseDemenage(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur);
};
