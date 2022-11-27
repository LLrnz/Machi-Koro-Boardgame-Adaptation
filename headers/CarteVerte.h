#pragma once

#include "Carte.h"
#include "Batiment.h"
#include <vector>
#include <string>
using namespace std;


class CarteVerte : public Batiment 
{
    string couleur;
public:
    void activer();
};
