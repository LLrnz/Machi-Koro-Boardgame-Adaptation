#include "../../headers/Cartes/MaisonEdition.h"
#include "../../headers/Jeu.h"
#include "../../headers/Controleur.h"

MaisonEdition::MaisonEdition(int id, std::string nom, TypeBatiment type,
                             int prix, int gain, std::vector<int> combinaisons,
                             Couleur couleur) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void MaisonEdition::activer(Joueur *joueurProprietaire)
{
    CarteViolette::activer(joueurProprietaire); // affichage de l'activation de la carte

    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur *controleur = Controleur::getControleur();

    int compteur = 0;
    for (auto &j : Jeu::getJeu().getJoueurs())
    {
        compteur = 0;
        for (auto &b : j.getConstructions())
            if (b->getType() == TypeBatiment::magasin || b->getType() == TypeBatiment::restaurant)
                compteur += 1;
        joueurActif->gagnerPieces(j.perdrePieces(compteur));
    }
}