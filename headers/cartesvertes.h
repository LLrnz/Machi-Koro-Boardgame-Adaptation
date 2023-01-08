#pragma once

#include "Batiment.h"
#include <vector>
#include <string>
#include "headers/enums.h"
using namespace std;

class CarteVerte : public Batiment
{
public:
    virtual void activer(Joueur *joueurProprietaire);
    CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
    virtual std::string to_string() const;
};


class EntrepriseDemenage : public CarteVerte
{
public:
    void activer(Joueur *joueurProprietaire);
    EntrepriseDemenage(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
};


class EntrepriseTravauxPub : public CarteVerte
{
public:
    void activer(Joueur *joueurProprietaire);
    EntrepriseTravauxPub(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
};


class Epicerie : public CarteVerte
{
public:
    void activer(Joueur *joueurProprietaire);
    Epicerie(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
};


class Fleuriste : public CarteVerte
{
public:
    void activer(Joueur *joueurProprietaire);
    Fleuriste(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description);
};


class MonsterSoda : public CarteVerte
{
private:
    TypeBatiment effectType;
public:
    void activer(Joueur *joueurProprietaire);
    MonsterSoda(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description, TypeBatiment effectType);
    TypeBatiment getEffectType() { return effectType; };
};


class VerteEffet : public CarteVerte
{
private:
    TypeBatiment effectType;
public:
    void activer(Joueur *joueurProprietaire);
    VerteEffet(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description, TypeBatiment effectType);
    TypeBatiment getEffectType() { return effectType; };
};
