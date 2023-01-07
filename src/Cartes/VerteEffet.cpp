#include "../../headers/Cartes/MonsterSoda.h"

MonsterSoda::MonsterSoda(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur)
{
    this->effectType = effectType;
}

void activer(Joueur *joueurProprietaire)
{
    int compteur = 0;
    for (auto &it : joueurActif->getConstructions())
    { // pour chaque batiment du joueur actif
        if (it->getType() == getEffectType())
        { // si le batiment est du type de l'effet
            compteur++;
        }
        if (compteur == 0)
            compteur = 1;
    }
    this->setGain(this->getGain() * compteur);
    CarteVerte::activer(joueurProprietaire);
}