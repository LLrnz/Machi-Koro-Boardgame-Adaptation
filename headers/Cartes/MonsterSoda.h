#pragma once

#include "CarteVerte.h"
#include <vector>
#include <string>
#include "headers/enums.h"
using namespace std;

class MonsterSoda : public CarteVerte
{
private:
    TypeBatiment effectType;
public:
    void activer(Joueur *joueurProprietaire);
    MonsterSoda(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType);
    TypeBatiment getEffectType() { return effectType; };
};
