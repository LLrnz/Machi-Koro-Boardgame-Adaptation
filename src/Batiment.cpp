#include "../headers/Batiment.h"

Batiment::Batiment(int id, std::string nom, TypeBatiment t, int prix, int gain, std::vector<int> combinaisons, Couleur c)
    : Carte(id, nom, prix), combinaisons(combinaisons), gain(gain), type(t), couleur(c) {

}