#pragma once

#include <iostream>

class InterfaceTerminal
{
public:
    void afficher(std::string f) const;
    std::string lire() const;
};
