#pragma once

#include <iostream>
#include <vector>

#include "../headers/enums.h"

class Batiment;
//class Monument;

class Joueur
{
    TypeJoueur type;
    std::string pseudo;
    int pieces;
    bool rejoueTour;
    std::vector<Batiment*> batiments;
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
    void setRejoueTour(bool b){rejoueTour = b;};

    int getPieces() const {return pieces;};
    void gagnerPieces(int nb){pieces += nb;};
    int perdrePieces(int nb);

    void ajouterBatiment(Batiment* b){batiments.push_back(b);};
};
