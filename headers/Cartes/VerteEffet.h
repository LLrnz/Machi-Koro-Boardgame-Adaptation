#pragma once

#include "CarteVerte.h"
#include <vector>
#include <string>
using namespace std;

class VerteEffet : public CarteVerte
{
private:
    TypeBatiment effectType;
public:
    void activer(Joueur *joueurProprietaire);
    VerteEffet(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType);
    TypeBatiment getEffectType() { return effectType; };
};
