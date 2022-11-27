#pragma once

#include "Carte.h"
#include "Batiment.h"
#include <vector>
#include <string>
using namespace std;


class CarteRouge : public Batiment 
{
    string couleur;
public:
    void activer();
};
