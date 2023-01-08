#pragma once

#include "Batiment.h"
#include "enums.h"
#include <vector>
#include <string>
#include "../headers/Joueur.h"

using namespace std;

class CarteViolette : public Batiment
{
public:
    virtual void activer(Joueur *joueurProprietaire); // cette méthode sera appelé par toute les classes filles pour l'affichage
    CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
    virtual std::string to_string() const;
};



class CentreAffaires : public CarteViolette
{
public:
    void activer(Joueur *joueurProprietaire);
    CentreAffaires(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
};



class CentreImpot : public CarteViolette
{
public:
    void activer(Joueur *joueurProprietaire);
    CentreImpot(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
};



class ChaineTV : public CarteViolette
{
public:
    void activer(Joueur *joueurProprietaire);
    ChaineTV(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
};


class MaisonEdition : public CarteViolette
{
public:
    void activer(Joueur *joueurProprietaire);
    MaisonEdition(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
};



class Stade : public CarteViolette
{
public:
    void activer(Joueur *joueurProprietaire);
    Stade(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
};
