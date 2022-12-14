#pragma once

#include <iostream>

class InterfaceTerminal
{
public:
    void afficher(std::string message) const;
    void afficher(int i) const;
    std::string lire() const;
};
