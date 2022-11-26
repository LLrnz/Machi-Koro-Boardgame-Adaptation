#pragma once

#include "Carte.h"
#include "enums.h"

class Monument : public Carte
{
    EnumEffet effet;
    bool construit;
};
