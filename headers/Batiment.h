#pragma once

#include "Carte.h"
#include <vector>
#include "enums.h"

using namespace std;
class Joueur; // Forward déclaration

class Batiment : public Carte
{
    std::vector<int> combinaisons;
    TypeBatiment type;
    int gain;
    Couleur couleur;

public:
    Batiment(int id, std::string nom, TypeBatiment t, int prix, int gain, std::vector<int> combinaisons, Couleur c);
    std::vector<int> getCombinaisons() const {return combinaisons;}
    TypeBatiment getType() const{return type;};
    Couleur getCouleur() const {return couleur;};
    int getGain()const{return gain;};
    virtual ~Batiment();
    virtual std::string to_string() const =0;
    virtual void activer(Joueur* joueurProprietaire) =0;

};
