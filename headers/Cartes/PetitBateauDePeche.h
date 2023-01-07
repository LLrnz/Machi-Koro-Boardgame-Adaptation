#pragma once

#include <vector>
#include <string>
#include "cartebleue.h"

using namespace std;

class PetitBateauDePeche : public CarteBleue
{
public:
    void activer(Joueur *joueurProprietaire);
    PetitBateauDePeche(int id, string nom, TypeBatiment type, int prix, int gain, vector<int> combinaisons, Couleur couleur);
    std::string to_string() const;
};