#include "../../headers/Cartes/ClubPrive.h"
#include "../../headers/Jeu.h"
#include "../../headers/Controleur.h"

ClubPrive::ClubPrive(int id, std::string nom, TypeBatiment type,
                     int prix, int gain, std::vector<int> combinaisons,
                     Couleur couleur, int nbMonuToActivate) : RougeNbBat(id, nom, type, prix, gain, combinaisons, couleur, nbMonuToActivate)
{
}

void ClubPrive::activer(Joueur *joueurProprietaire)
{
    Jeu &jeu = Jeu::getJeu();
    Joueur *joueurActif = jeu.getJoueurActif();
    
    this->setGain(joueurActif->getPieces());
    ClubPrive::activer(joueurProprietaire);
}