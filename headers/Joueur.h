#pragma once

#include <iostream>
#include <vector>

#include "enums.h"

class Batiment;
//class Monument;

class Joueur
{
    TypeJoueur type;
    std::string pseudo;
    int pieces;
    bool rejoueTour;
    std::vector<Batiment*> constructions;
    //std::vector<Monument> monuments;

public:
    Joueur(std::string psdo, TypeJoueur typ);
    bool hasDoubleDes() const;
    bool hasDoubleProduction() const;
    bool hasRejouerDouble() const;
    bool hasRelancerDes() const;
    bool hasPort() const;
    bool hasAeroport()const;
    void activerCartesBleues();
    void activerCartesVertes();
    void activerCartesRouges();
    void activerCartesViolettes();
    void gagnerPieces();
    void setRejoueTour(bool b){rejoueTour = b;};
};
