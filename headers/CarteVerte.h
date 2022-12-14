#pragma once

#include "Batiment.h"
#include <vector>
#include <string>
using namespace std;


class CarteVerte : public Batiment 
{
public:
    void activer();
    CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur);
};
