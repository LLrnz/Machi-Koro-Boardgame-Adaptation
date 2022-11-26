#ifndef BATIMENT_H
#define BATIMENT_H
#include <Carte.h>


class Batiment : public Carte
{
    list<int> activation;
    int gain;
public:
    void activer();
};





#endif // BATIMENT_H
