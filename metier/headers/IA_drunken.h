#ifndef IA_DRUNKEN_H
#define IA_DRUNKEN_H
#include "../../metier/headers/Joueur.h"
#include "../../metier/headers/IA.h"
#endif // IA_DRUNKEN_H
class IA_drunken: public IA{
public :
    IA_drunken(std::string pseudo)
        : IA(pseudo){}

    ~IA_drunken();
    int choixDes();

    Carte* choixAchat(vector<Carte*> cartes);
    Joueur* choixJoueur(vector<Joueur*> joueurs);
    Batiment* choixBatiment(vector<Batiment*> batiments);
    int choixPort();
    bool choixRelance();
};
