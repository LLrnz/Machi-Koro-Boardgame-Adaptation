#pragma once

#include "Carte.h"
#include <vector>
#include "enums.h"


class Batiment : public Carte
{
    std::vector<int> combinaisons;
    int gain;
    TypeBatiment type;
public:
    Batiment(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons);
    void activer();
};
