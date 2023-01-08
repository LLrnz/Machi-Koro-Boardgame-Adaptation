#include "metier/headers/cartesbleues.h"
#include "metier/headers/Controleur.h"
#include "metier/headers/Joueur.h"
#include <sstream>

CarteBleue::CarteBleue(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void CarteBleue::activer(Joueur *joueurProprietaire)
{
    string name = this->getNom();
    Controleur *controleur = Controleur::getControleur();

    controleur->afficher(joueurProprietaire->getPseudo() + " a activé la carte bleue " + this->getNom() + "\n");

    joueurProprietaire->gagnerPieces(getGain());
    controleur->afficher(joueurProprietaire->getPseudo() + " gagne " + std::to_string(this->getGain()) + "\n");
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


Chalutier::Chalutier(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description)
    : CarteBleue(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

std::string Chalutier::to_string() const
{
    std::string res = "[" + this->getNom() + "] \e[0;93m" + std::to_string(this->getPrix()) + "p\e[0m : lance 2 dés est donne ce nombre de pièces sur (";
    for (const auto &i : this->getCombinaisons())
    {
        res += std::to_string(i);
        res += ",";
    }
    res += ") aux dés.";
    return res;
}

void Chalutier::activer(Joueur *joueurProprietaire)
{
    if (joueurProprietaire->hasPort())
    { // si c'est un chalutier et que le joueur a un bateau de pêche
        int de1 = (rand() % 6) + 1;
        int de2 = (rand() % 6) + 1;
        int resultatJet = de1 + de2;

        this->setGain(resultatJet);
        CarteBleue::activer(joueurProprietaire);
    }
}


PetitBateauDePeche::PetitBateauDePeche(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description)
    : CarteBleue(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

std::string PetitBateauDePeche::to_string() const
{
    std::string res = "[" + this->getNom() + "] \e[0;93m" +std::to_string(this->getPrix()) + "p\e[0m : produit <" + std::to_string(this->getGain()) + "> pièces, si le joueur à le port, sur (" ;
    for(const auto &i : this->getCombinaisons()){
        res += std::to_string(i);
        res += ",";
    }
    res += ") aux dés.";
    return res;
}

void PetitBateauDePeche::activer(Joueur *joueurProprietaire)
{
    if (joueurProprietaire->hasPort())
    { // si le joueur a le port
        CarteBleue::activer(joueurProprietaire);
    }
};
