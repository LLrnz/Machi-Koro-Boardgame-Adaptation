#include "../../headers/Cartes/Stade.h"
#include "../../headers/Jeu.h"
#include "../../headers/Controleur.h"

Stade::Stade(int id, std::string nom, TypeBatiment type,
             int prix, int gain, std::vector<int> combinaisons,
             Couleur couleur) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void Stade::activer(Joueur *joueurProprietaire)
{
    CarteViolette::activer(joueurProprietaire); // affichage de l'activation de la carte

    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur *controleur = Controleur::getControleur();

    for (auto &j : Jeu::getJeu().getJoueurs())
    {
        if (&j != joueurActif)
        {
            joueurActif->gagnerPieces(j.perdrePieces(2));
        }
    }
}