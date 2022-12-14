#pragma once

#include "Carte.h"
#include "Batiment.h"
#include "Enums.h"
#include <vector>
#include <string>
using namespace std;


class CarteViolette : public Batiment 
{
    Source source;
public:
    void activer();
    CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Source source);
};
