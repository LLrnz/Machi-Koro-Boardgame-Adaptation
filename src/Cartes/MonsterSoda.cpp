#include "../../headers/Cartes/MonsterSoda.h"

MonsterSoda::MonsterSoda(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur)
{
    this->effectType = effectType;
}

void activer(Joueur *joueurProprietaire)
{
    int compteur = 0;
    for (auto &i : Jeu::getJeu().getJoueurs())
    { // pour chaque joueur
        for (auto &j : i.getConstructions())
        {                                        // pour chaque batiment du joueur
            if (j->getType() == getEffectType()) // si le batiment est du type de l'effet
                compteur++;
        }
    }
    this->setGain(compteur);
    CarteVerte::activer(joueurProprietaire);
}