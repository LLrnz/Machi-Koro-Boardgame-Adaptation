#pragma once

#include "Batiment.h"
#include <vector>
#include <string>
using namespace std;


class CarteBleue : public Batiment 
{
    string couleur;
public:
    void activer();
    CarteBleue(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons);
};
