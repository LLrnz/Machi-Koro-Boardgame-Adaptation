#pragma once

#include "CarteVerte.h"
#include <vector>
#include <string>
using namespace std;

class Epicerie : public CarteVerte
{
public:
    void activer(Joueur *joueurProprietaire);
    Epicerie(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur);
    std::string to_string() const;
};
