#pragma once

#include "Carte.h"
#include "enums.h"

class Monument : public Carte
{
    TypeBatiment effet;
    bool construit;
};
