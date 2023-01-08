#include "../../metier/headers/cartesrouges.h"
#include "../../metier/headers/Jeu.h"
#include "../../metier/headers/Controleur.h"
#include <sstream>

CarteRouge::CarteRouge(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur, description)
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


BarASushi::BarASushi(int id, std::string nom, TypeBatiment type,
                     int prix, int gain, std::vector<int> combinaisons,
                     Couleur couleur, std::string description) : CarteRouge(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void BarASushi::activer(Joueur *joueurProprietaire)
{
    if (joueurProprietaire->hasPort()) {
        CarteRouge::activer(joueurProprietaire);
    }
}


RougeNbBat::RougeNbBat(int id, std::string nom, TypeBatiment type,
                       int prix, int gain, std::vector<int> combinaisons,
                       Couleur couleur, std::string description,  int nbMonuToActivate) : CarteRouge(id, nom, type, prix, gain, combinaisons, couleur, description)
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


ClubPrive::ClubPrive(int id, std::string nom, TypeBatiment type,
                     int prix, int gain, std::vector<int> combinaisons,
                     Couleur couleur, std::string description, int nbMonuToActivate) : RougeNbBat(id, nom, type, prix, gain, combinaisons, couleur, description, nbMonuToActivate)
{
}

void ClubPrive::activer(Joueur *joueurProprietaire)
{
    Jeu &jeu = Jeu::getJeu();
    Joueur *joueurActif = jeu.getJoueurActif();
    
    this->setGain(joueurActif->getPieces());
    CarteRouge::activer(joueurProprietaire);
}
