#pragma once

#include "Carte.h"
#include <vector>
#include "enums.h"


class Batiment : public Carte
{
    std::vector<int> combinaisons;
    TypeBatiment type;
    int gain;
    Couleur couleur;
public:
    Batiment(int id, std::string nom, TypeBatiment t, int prix, int gain, std::vector<int> combinaisons, Couleur c);
    std::vector<int> getCombinaisons() const {return combinaisons;}
    TypeBatiment getType() const;
    Couleur getCouleur() const;
    void activer(){}
};


