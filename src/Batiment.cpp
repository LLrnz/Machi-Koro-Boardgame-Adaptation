#include "../headers/Batiment.h"
#include "../headers/Jeu.h"

Batiment::Batiment(int id, std::string nom, TypeBatiment t, int prix, int gain, std::vector<int> combinaisons, Couleur c, std::string description)
    : Carte(id, nom, prix), combinaisons(combinaisons), type(t), gain(gain), couleur(c), description(description) {

}

Batiment::~Batiment(){};

void Batiment::acheter(){
    Jeu::getJeu().getJoueurActif()->ajouterBatiment(this);
    Jeu::getJeu().getMarche()->acheter(this);
};
