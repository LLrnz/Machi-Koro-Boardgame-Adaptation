#pragma once

#include "CarteVerte.h"
#include <vector>
#include <string>
using namespace std;

class EntrepriseTravauxPub : public CarteVerte
{
public:
    void activer(Joueur *joueurProprietaire);
    EntrepriseTravauxPub(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur);
};
