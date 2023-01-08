#pragma once

#include <vector>
#include <string>
#include "Batiment.h"

using namespace std;

class CarteBleue : public Batiment
{
public:
    virtual void activer(Joueur *joueurProprietaire);
    CarteBleue(int id, string nom, TypeBatiment type, int prix, int gain, vector<int> combinaisons, Couleur couleur, std::string description);
    virtual std::string to_string() const;
};

class Chalutier : public CarteBleue
{
public:
    void activer(Joueur* joueurProprietaire);
    Chalutier(int id, string nom, TypeBatiment type, int prix, int gain, vector<int> combinaisons, Couleur couleur, std::string description);
    std::string to_string() const;
};

class PetitBateauDePeche : public CarteBleue
{
public:
    void activer(Joueur *joueurProprietaire);
    PetitBateauDePeche(int id, string nom, TypeBatiment type, int prix, int gain, vector<int> combinaisons, Couleur couleur, std::string description);
    std::string to_string() const;
};
