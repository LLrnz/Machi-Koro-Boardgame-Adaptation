#include "../../headers/Cartes/CarteVerte.h"
#include "../../headers/Jeu.h"
#include "../../headers/Controleur.h"
#include <sstream>

CarteVerte::CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur) {}

void CarteVerte::activer(Joueur *joueurProprietaire)
{
    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();
    vector<Joueur> joueurs = Jeu::getJeu().getJoueurs();

    Controleur::getControleur()->afficher(this->getNom() + " vous a rapporté " + std::to_string(this->getGain()) + " pièces.\n");
    joueurActif->gagnerPieces(this->getGain());
}

std::string CarteVerte::to_string() const
{
    std::string res = "[" + this->getNom() + "] \e[0;93m" + std::to_string(this->getPrix()) + "p\e[0m : produit <" + std::to_string(this->getGain()) + "> pièces sur (";
    for (const auto &i : this->getCombinaisons())
    {
        res += std::to_string(i);
        res += ", ";
    }
    res += ") aux dés, ";

    return res;
}
