#pragma once


#include <vector>
#include <string>
#include "../headers/Batiment.h"

using namespace std;


class CarteBleue : public Batiment
{
public:
    virtual void activer(Joueur* joueurProprietaire);
    CarteBleue(int id, string nom, TypeBatiment type, int prix, int gain, vector<int> combinaisons, Couleur couleur);
    std::string to_string() const;
};
