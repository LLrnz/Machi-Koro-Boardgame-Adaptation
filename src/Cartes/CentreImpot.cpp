#include "../../headers/Cartes/CentreImpot.h"
#include "../../headers/Jeu.h"
#include <cmath>

CentreImpot::CentreImpot(int id, std::string nom, TypeBatiment type,
                         int prix, int gain, std::vector<int> combinaisons,
                         Couleur couleur) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void CentreImpot::activer(Joueur *joueurProprietaire)
{
    CarteViolette::activer(joueurProprietaire); // affichage de l'activation de la carte

    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();

    for (auto &j : Jeu::getJeu().getJoueurs())
    {
        if (j.getPieces() >= 10)
            joueurActif->gagnerPieces(j.perdrePieces(floor(j.getPieces() / 2)));
    }
}
