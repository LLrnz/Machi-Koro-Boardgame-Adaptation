#pragma once

#include "Batiment.h"
#include <vector>
#include <string>
using namespace std;

class CarteRouge : public Batiment
{

private:
    int nbMonuToActivate; // nombre de monument requis pour pouvoir construire le batiment
public:
    virtual void activer(Joueur *joueurProprietaire);
    CarteRouge(int id, std::string nom, TypeBatiment type,
               int prix, int gain, std::vector<int> combinaisons,
               Couleur couleur);
    void setGain(int gain) { this->gain = gain; };
    virtual std::string to_string() const;
};
