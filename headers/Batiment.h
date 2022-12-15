#pragma once

#include "Carte.h"
#include <vector>
#include "enums.h"
using namespace std;

class Batiment : public Carte
{
    vector<int> combinaisons;
    int gain;
    TypeBatiment type;
public:
    Batiment(int id, string nom, TypeBatiment type, int prix, int gain, vector<int> combinaisons);
    void activer();
    TypeBatiment getType() const {return type;};
};
