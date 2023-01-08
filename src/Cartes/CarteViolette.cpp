#include "../../headers/Cartes/CarteViolette.h"
#include "../../headers/enums.h"
#include "../../headers/Controleur.h"
#include <cmath>

CarteViolette::CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur)
{
}
void CarteViolette::activer(Joueur *joueurProprietaire)
{
    string name = this->getNom();
    Controleur *controleur = Controleur::getControleur();

    controleur->afficher("Vous avez activé la carte " + name + "\n");

}

std::string CarteViolette::to_string() const
{
    std::string res = "[" + this->getNom() + "] \e[0;93m" + std::to_string(this->getPrix()) + "p\e[0m : produit <" + std::to_string(this->getGain()) + "> pièces sur (";
    for (const auto &i : this->getCombinaisons())
    {
        res += std::to_string(i);
        res += ", ";
    }
    res += ") aux dés, ";

    switch (getId())
    {
    case 13: // stade
        res += "Insérer effet";
        break;

    case 14: // chaineTV
        res += "Insérer effet";
        break;

    case 15: // centreAffaires
        res += "Insérer effet";
        break;
    }
    return res;
}
