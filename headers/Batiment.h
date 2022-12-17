#pragma once

#include "Carte.h"
#include <vector>
#include "enums.h"
using namespace std;


class Batiment : public Carte
{
    std::vector<int> combinaisons;
    TypeBatiment type;
    int gain;
    Couleur couleur;
public:
    Batiment(int id, std::string nom, TypeBatiment t, int prix, int gain, std::vector<int> combinaisons, Couleur c);
    std::vector<int> getCombinaisons() {return combinaisons;}
    TypeBatiment getType() const{return type;};
    Couleur getCouleur() const {return couleur;};
    int getGain()const{return gain;};
    virtual void activer(){};
};
