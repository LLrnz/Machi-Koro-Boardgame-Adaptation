#pragma once

#include "Carte.h"
#include "Batiment.h"
#include "enums.h"
#include <vector>
#include <string>
#include "../headers/Joueur.h"
using namespace std;


class CarteViolette : public Batiment {
public:
    virtual void activer(Joueur joueurProprietaire);
    CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur);
};
