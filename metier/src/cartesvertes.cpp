#include "../../metier/headers/cartesvertes.h"
#include "../../metier/headers/Jeu.h"
#include "../../metier/headers/Controleur.h"
#include "../../metier/headers/Joueur.h"
#include <sstream>
#include <vector>

CarteVerte::CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur, description) {}

void CarteVerte::activer(Joueur *joueurProprietaire)
{
    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();
    vector<Joueur*> joueurs = Jeu::getJeu().getJoueurs();

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



VerteEffet::VerteEffet(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description, TypeBatiment effectType)
    : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur, description)
{
    this->effectType = effectType;
}

void VerteEffet::activer(Joueur *joueurProprietaire)
{
    int compteur = 0;
    for (auto &it : joueurProprietaire->getConstructions())
    { // pour chaque batiment du joueur actif
        if (it->getType() == this->getEffectType())
        { // si le batiment est du type de l'effet
            compteur++;
        }
        if (compteur == 0)
            compteur = 1;
    }
    this->setGain(this->getGain() * compteur);
    CarteVerte::activer(joueurProprietaire);
}



EntrepriseDemenage::EntrepriseDemenage(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description) : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void EntrepriseDemenage::activer(Joueur *joueurProprietaire)
{
    Controleur::getControleur()->afficher("Liste des cartes possibles à déménager : \n"); // on affiche les cartes possibles à déménager
    vector<Batiment *> choixBatiments;
    for (auto &b : joueurProprietaire->getConstructions())
    { // pour chaque batiment du joueur actif
        if (b->getType() != TypeBatiment::special)
            choixBatiments.push_back(b);
    }

    Controleur::getControleur()->afficher("Votre choix : \n");
    Batiment *batimentChoisi = Controleur::getControleur()->selection_batiment(choixBatiments);

    Controleur::getControleur()->afficher("Choisisez un AUTRE joueur à qui gracieusement donner cette carte \n");
    // On peut choisir tous les joueurs sauf le joueur actif

    Joueur *joueurChoisi = Controleur::getControleur()->selection_joueur(Jeu::getJeu().getJoueursSansActifPtr());

    joueurChoisi->ajouterBatiment(batimentChoisi);
    joueurProprietaire->enleverBatiment(batimentChoisi);
    this->setGain(4);
    CarteVerte::activer(joueurProprietaire);
}



EntrepriseTravauxPub::EntrepriseTravauxPub(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description)
    : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void EntrepriseTravauxPub::activer(Joueur *joueurProprietaire)
{
    std::vector<Monument *> monumentsVendables;
    Controleur::getControleur()->afficher("Liste des monuments construits : \n");
    for (auto &monu : joueurProprietaire->getMonuments())
    {
        if (monu->getConstruit())
        {
            monumentsVendables.push_back(monu);
        }
    }

    if (!monumentsVendables.empty())
    {
        Controleur::getControleur()->afficher("Choisisez le monument à detruire pour gagner 8 pièces \n");
        Monument *reponse = Controleur::getControleur()->selection_monument(monumentsVendables);
        reponse->detruire();
        this->setGain(8);
    }
    else
    {
        Controleur::getControleur()->afficher("Vous n'avez aucun monument à vendre \n");
        this->setGain(0);
    }
    CarteVerte::activer(joueurProprietaire);
}


Epicerie::Epicerie(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description) : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void Epicerie::activer(Joueur *joueurProprietaire)
{
    if (joueurProprietaire->getNbMonumentsConstruits() >= 2)
    {
        CarteVerte::activer(joueurProprietaire);
    }
}


Fleuriste::Fleuriste(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description) : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void Fleuriste::activer(Joueur *joueurProprietaire)
{
    int compteur = 0;
    for (auto &it : joueurProprietaire->getConstructions())
    {                         // pour chaque batiment du joueur actif
        if (it->getId() == 9) // si le batiment est un champ de fleurs (voir CarteBleue.cpp)
            compteur += 1;
    }
    this->setGain(compteur);
    CarteVerte::activer(joueurProprietaire);
}
