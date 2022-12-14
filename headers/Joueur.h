#pragma once

#include <iostream>
#include <vector>

#include "enums.h"
#include "headers/Monument.h"

class Batiment;
class Monument;

class Joueur
{
    TypeJoueur type;
    std::string pseudo;
    int pieces;
    bool rejoueTour;
    std::vector<Batiment*> constructions;
    std::vector<Monument> monuments;

public:
    Joueur(std::string psdo, TypeJoueur typ);
    bool hasDoubleDes() const;
    bool hasDoubleProduction() const;
    bool hasRejouerDouble() const;
    bool hasRelancerDes() const;
    bool hasPort() const;
    bool hasAeroport()const;
    void extracted(int &nbDes, std::vector<Batiment *>::iterator &it,
                   bool &bonNombreAuDe);
    void activerCartesBleues(int nbDes);
    void activerCartesVertes(int nbDes);
    void activerCartesRouges(int nbDes);
    void activerCartesViolettes(int nbDes);
    void gagnerPieces();
    void setRejoueTour(bool b){rejoueTour = b;};
};
