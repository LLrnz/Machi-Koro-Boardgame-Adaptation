#include "../../headers/Cartes/Epicerie.h"

Epicerie::Epicerie(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur) : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void Epicerie::activer(Joueur *joueurProprietaire)
{
    if (joueurActif->getNbMonumentsConstruits() >= 2)
    {
        CarteVerte::activer(joueurProprietaire);
    }
}