#pragma once

#include <iostream>

class InterfaceTerminal
{
public:
    void afficher(std::string f) const;
    std::string lire() const;
    int lire_int();
    int lire_int(int x, int y);

};
