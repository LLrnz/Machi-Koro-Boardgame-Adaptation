#pragma once

#include <iostream>
#include "Controleur.h"

class InterfaceTerminal
{
public:
    void afficher(ostream& f) const;
    ostream& lire() const;
};
