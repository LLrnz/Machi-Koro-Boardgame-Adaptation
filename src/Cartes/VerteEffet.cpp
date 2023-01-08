#include "../../headers/Cartes/VerteEffet.h"
#include "headers/Joueur.h"

VerteEffet::VerteEffet(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType)
    : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur)
{
    this->effectType = effectType;
}

void VerteEffet::activer(Joueur *joueurProprietaire)
{
    int compteur = 0;
    for (auto &it : joueurProprietaire->getConstructions())
    { // pour chaque batiment du joueur actif
        if (it->getType() == this->getEffectType())
        { // si le batiment est du type de l'effet
            compteur++;
        }
        if (compteur == 0)
            compteur = 1;
    }
    this->setGain(this->getGain() * compteur);
    CarteVerte::activer(joueurProprietaire);
}
