#include "../../headers/Cartes/CarteRouge.h"
#include "../../headers/Jeu.h"
#include "../../headers/Controleur.h"
#include <sstream>

CarteRouge::CarteRouge(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void CarteRouge::activer(Joueur *joueurProprietaire)
{
    Jeu &jeu = Jeu::getJeu();
    string name = this->getNom();
    Joueur *joueurActif = jeu.getJoueurActif();
    Controleur *controleur = Controleur::getControleur();

    // id : 1 = Café, 2 = Restaurant, 3 = Pizzeria, 4 = Moonster burdcger, 5 = Bar a sushi
    // id : 6 = Club privé, 7 = Restaurant gastronomique
    
    joueurActif->perdrePieces(this->getGain());        // le joueur actif perd des pieces
    joueurProprietaire->gagnerPieces(this->getGain()); // le joueur proprietaire gagne des pieces

    // affichage
    stringstream s;
    s << joueurActif->getPseudo() << " a payé " << this->getGain() << " pièces à " << joueurProprietaire->getPseudo() << endl;
    controleur->afficher(s.str());
}

std::string CarteRouge::to_string() const
{
    std::string res = "[" + this->getNom() + "] \e[0;93m" + std::to_string(this->getPrix()) + "p\e[0m : vole <" + std::to_string(this->getGain()) + "> pièces au joueur actif s'il a au moins " + std::to_string(this->nbMonuToActivate) + " monuments construits. S'active sur (";
    for (const auto &i : this->getCombinaisons())
    {
        res += std::to_string(i);
        res += ", ";
    }
    res += ") aux dés.";
    return res;
}
