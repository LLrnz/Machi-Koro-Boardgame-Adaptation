#pragma once

#include <iostream>
#include "Controlleur.h"

class Jeu
{
 public:
    void afficher(ostream& f) const;
    ostream& lire() const;
}
