#ifndef JOUEUR_H
#define JOUEUR_H
#include "Batiment.h"
#include "Monument.h"

enum class TypeJoueur { humain, IA };

class Joueur
{
    TypeJoueur type;
    string pseudo;
    int pieces;
    list<Batiment&> constructions;
    list<Monument> monuments;

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

#endif // JOUEUR_H
