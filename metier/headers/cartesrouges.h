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
               Couleur couleur, std::string description);
    virtual std::string to_string() const;
};


class BarASushi : public CarteRouge
{

private:
    int nbMonuToActivate; // nombre de monument requis pour pouvoir construire le batiment
public:
    void activer(Joueur *joueurProprietaire);
    BarASushi(int id, std::string nom, TypeBatiment type,
               int prix, int gain, std::vector<int> combinaisons,
               Couleur couleur, std::string description);
};


class RougeNbBat : public CarteRouge
{

private:
    int nbMonuToActivate; // nombre de monument requis pour pouvoir construire le batiment
public:
    virtual void activer(Joueur *joueurProprietaire);
    RougeNbBat(int id, std::string nom, TypeBatiment type,
               int prix, int gain, std::vector<int> combinaisons,
               Couleur couleur, std::string description, int nbMonuToActivate);
    int getNbMonuToActivate() const { return nbMonuToActivate;}
};

class ClubPrive : public RougeNbBat
{
public:
    virtual void activer(Joueur *joueurProprietaire);
    ClubPrive(int id, std::string nom, TypeBatiment type,
               int prix, int gain, std::vector<int> combinaisons,
               Couleur couleur, std::string description, int nbMonuToActivate);
};

