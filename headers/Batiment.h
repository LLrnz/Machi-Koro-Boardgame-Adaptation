#pragma once

#include "Carte.h"
#include <vector>


class Batiment : public Carte
{
    std::vector<int> activation;
    int gain;
public:
    void activer();
};


