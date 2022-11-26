#ifndef MONUMENT_H
#define MONUMENT_H
#include <Carte.h>

enum class EnumEffet { deuxDes, doubleProduction, rejouerDouble, relancerDes };

class Monument : public Carte
{
    EnumEffet effet;
    bool construit;
};

#endif // MONUMENT_H
