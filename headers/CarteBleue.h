#pragma once

#include "Carte.h"
#include "Batiment.h"
#include <vector>
#include <string>
using namespace std;


class CarteBleue : public Batiment 
{
    string couleur;
public:
    void activer();
};
