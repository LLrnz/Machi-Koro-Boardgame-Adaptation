#include "../../headers/Cartes/ChaineTV.h"
#include "../../headers/Jeu.h"
#include "../../headers/Controleur.h"

ChaineTV::ChaineTV(int id, std::string nom, TypeBatiment type,
             int prix, int gain, std::vector<int> combinaisons,
             Couleur couleur) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void ChaineTV::activer(Joueur *joueurProprietaire)
{
    CarteViolette::activer(joueurProprietaire); // affichage de l'activation de la carte

    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur *controleur = Controleur::getControleur();

    controleur->afficher("A qui voulez vous prendre 5 pieces ? \n");

    Joueur *joueurChoisi = controleur->selection_joueur(Jeu::getJeu().getJoueursSansActifPtr());
    int vol = joueurChoisi->perdrePieces(5);
    joueurActif->gagnerPieces(vol);
}