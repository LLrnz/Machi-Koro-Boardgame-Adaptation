#include "../../headers/Cartes/PetitBateauDePeche.h"

PetitBateauDePeche::PetitBateauDePeche(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : CarteBleue(id, nom, type, prix, gain, combinaisons, couleur)
{
}

std::string PetitBateauDePeche::to_string() const
{
    std::string res = "[" + this->getNom() + "] \e[0;93m" +std::to_string(this->getPrix()) + "p\e[0m : produit <" + std::to_string(this->getGain()) + "> pièces,
    si le joueur à le port, sur (" ;
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
}