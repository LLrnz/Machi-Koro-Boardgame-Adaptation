#pragma once

#include "Carte.h"
#include "Batiment.h"
#include "Enums.h"
#include <vector>
#include <string>
using namespace std;


class Carteviolette : public Batiment 
{
    string couleur;
    Source source;
public:
    void activer();
};
