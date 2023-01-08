#include "../../headers/Cartes/RougeNbBat.h"
#include "headers/Jeu.h"

RougeNbBat::RougeNbBat(int id, std::string nom, TypeBatiment type,
                       int prix, int gain, std::vector<int> combinaisons,
                       Couleur couleur, int nbMonuToActivate) : CarteRouge(id, nom, type, prix, gain, combinaisons, couleur)
{
    this->nbMonuToActivate = nbMonuToActivate;
}

void RougeNbBat::activer(Joueur *joueurProprietaire)
{
    Jeu &jeu = Jeu::getJeu();
    Joueur *joueurActif = jeu.getJoueurActif();
    int compteur = 0;
    for (size_t i = 0; i < size(joueurActif->getMonuments()); i++)
    {                                                               // pour chaque monument du joueur actif
        if (joueurActif->getMonuments()[i]->getConstruit() == true) // si le monument est construit
            compteur += 1;                                          // on incremente le compteur
    }
    if (compteur >= this->getNbMonuToActivate())
    {           // si le joueur a assez de monument construit
        CarteRouge::activer(joueurProprietaire); // on active la carte
    }
}
