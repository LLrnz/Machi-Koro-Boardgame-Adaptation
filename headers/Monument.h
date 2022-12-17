#pragma once

#include "Carte.h"
#include <string>


class Monument : public Carte
{
    bool construit;
public:
    Monument(std::string n,int p):Carte(0,n,p),construit(false){}
    bool getConstruit() const {return construit;}
    void setConstruit() {construit = true;}
    void detruire() {construit=false;}
    std::string to_string() const;
};
