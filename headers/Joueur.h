#pragma once

#include <iostream>
#include <vector>

#include "enums.h"

class Batiment;
class Monument;

class Joueur
{
    TypeJoueur type;
    std::string pseudo;
    int pieces;
    std::vector<Batiment*> constructions;
    std::vector<Monument> monuments;

public:
    bool hasDoubleDes() const;
    bool hasDoubleProduction() const;
    bool hasRejouerDouble() const;
    bool hasRelancerDes() const;
    void activerCartesBleues();
    void activerCartesVertes();
    void activerCartesRouges();
    void activerCartesViolettes();
    void gagnerPieces();
};
