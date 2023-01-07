#include "../../headers/Cartes/Fleuriste.h"

Fleuriste::Fleuriste(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur) : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void Fleuriste::activer(Joueur *joueurProprietaire)
{
    int compteur = 0;
    for (auto &it : joueurActif->getConstructions())
    {                         // pour chaque batiment du joueur actif
        if (it->getId() == 9) // si le batiment est un champ de fleurs (voir CarteBleue.cpp)
            compteur += 1;
    }
    this->setGain(compteur)
    CarteVerte::activer(joueurProprietaire);
}