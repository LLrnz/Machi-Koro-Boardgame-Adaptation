#pragma once

#include "Carte.h"
#include "Batiment.h"
#include <vector>
#include <string>
using namespace std;


class CarteRouge : public Batiment 
{
public:
    void activer(Joueur joueurProprietaire);
    CarteRouge(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur);
};
