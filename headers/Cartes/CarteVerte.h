#pragma once

#include "../Batiment.h"
#include <vector>
#include <string>
using namespace std;

class CarteVerte : public Batiment
{
public:
    virtual void activer(Joueur *joueurProprietaire);
    CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur);
    virutal std::string to_string() const;
    void setGain(int gain) {
        this->gain = gain;
    }
};