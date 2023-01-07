#include "../../headers/Cartes/CarteBleue.h"
#include "../../headers/Controleur.h"
#include <sstream>

CarteBleue::CarteBleue(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void CarteBleue::activer(Joueur *joueurProprietaire)
{
    string name = this->getNom();
    Controleur *controleur = Controleur::getControleur();

    controleur->afficher(joueurProprietaire->getPseudo() + " a activé la carte bleue " + this->getNom() + "\n");

    joueurProprietaire->gagnerPieces(getGain());
    controleur->afficher(joueurProprietaire->getPseudo() + " gagne " + std::to_string(gain) + "\n");
}

std::string CarteBleue::to_string() const
{
    std::string res = "[" + this->getNom() + "] \e[0;93m" + std::to_string(this->getPrix()) + "p\e[0m : produit <" + std::to_string(this->getGain()) + "> pièces sur (";
    for (const auto &i : this->getCombinaisons())
    {
        res += std::to_string(i);
        res += ",";
    }
    res += ") aux dés.";
    return res;
}
