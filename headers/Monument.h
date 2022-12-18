#pragma once

#include "Carte.h"
#include <string>


class Monument : public Carte
{
    bool construit;
public:
    Monument(std::string n,int p);

    virtual void acheter();
    virtual ~Monument();
    std::string to_string() const;


    bool getConstruit() const {return construit;}
    void setConstruit() {construit = true;}
    void detruire() {construit=false;}


};
