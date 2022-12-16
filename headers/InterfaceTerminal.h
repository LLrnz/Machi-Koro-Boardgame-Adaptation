#pragma once

#include <iostream>

class InterfaceTerminal
{
public:
    void afficher(std::string f) const;
    void afficher(int i) const {std::cout << i;};
    std::string lire() const;
    int lire_int();
    int lire_int(int x, int y);

};
