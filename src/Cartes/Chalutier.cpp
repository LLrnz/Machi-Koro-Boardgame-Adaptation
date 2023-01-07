#include "../../headers/Cartes/Chalutier.h"

Chalutier::Chalutier(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : CarteBleue(id, nom, type, prix, gain, combinaisons, couleur)
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

        this->gain = resultatJet;
        CarteBleue::activer(joueurProprietaire);
    }
}