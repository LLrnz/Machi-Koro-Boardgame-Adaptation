#pragma once


#include <vector>
#include <string>
#include "CarteBleue.h"

using namespace std;

class Chalutier : public CarteBleue
{
public:
    activer(Joueur* joueurProprietaire);
    Chalutier(int id, string nom, TypeBatiment type, int prix, int gain, vector<int> combinaisons, Couleur couleur);
    std::string to_string() const;
};

