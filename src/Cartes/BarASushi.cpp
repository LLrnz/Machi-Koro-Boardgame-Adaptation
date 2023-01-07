#include "../../headers/Cartes/BarASushi.h"

BarASushi::BarASushi(int id, std::string nom, TypeBatiment type,
                     int prix, int gain, std::vector<int> combinaisons,
                     Couleur couleur) : CarteRouge(id, nom, type, prix, gain, combinaisons, couleur)
{
}

BarASushi::activer(Joueur* joueurProprietaire)
{
    if (joueurProprietaire->hasPort()) {
        CarteRouge::activer(joueurProprietaire);
    }
}