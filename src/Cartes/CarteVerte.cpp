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

    Controleur::getControleur()->afficher(this->getNom() + " vous a rapporté " + std::to_string(gain) + " pièces.\n");
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

    switch (getId())
    {
    case 10: // Moonster soda
        res += "gagnez le gain pour chaque carte restaurant construite.";
        break;

    case 8: // Epicerie
        res += "gagnez le gain si vous avez moins de 2 monuments construits";
        break;

    case 6: // Fleuriste
        res += "pour chaque carte Jardin de fleur construite.";
        break;

    case 9: // Entreprise de travaux publics
        res += "Détruisez un monument pour gagner 8 pièces.";
        break;

    case 11: // Entreprise de déménagement
        res += "vous gagnez les pièces en donnant un de vos batiments non spécial à un autre joueur.";
        break;
    }

    return res;
}
