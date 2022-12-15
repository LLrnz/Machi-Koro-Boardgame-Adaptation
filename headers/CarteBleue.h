#pragma once

#include "Batiment.h"
#include <vector>
#include <string>
using namespace std;


class CarteBleue : public Batiment 
{
public:
    void activer(Joueur joueurProprietaire);
    CarteBleue(int id, string nom, TypeBatiment type, int prix, int gain, vector<int> combinaisons, Couleur couleur);
};
