#pragma once

#include "Carte.h"
#include <string>


class Monument : public Carte
{
    bool construit;
public:
    Monument(std::string n,int p);

    virtual void acheter(); //Méthode virtual de carte
    virtual ~Monument();
    virtual std::string to_string() const{return "";};


    bool getConstruit() const {return construit;}
    void setConstruit() {construit = true;}
    void detruire() {construit=false;}
};
