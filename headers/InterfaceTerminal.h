#pragma once

#include <iostream>
#include "Controleur.h"

class InterfaceTerminal
{
public:
    void afficher(string message) const;
    void afficher(int i) const;
    string& lire() const;
};
