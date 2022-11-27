#include "./../headers/Batiment.h"

Batiment::Batiment(int id, std::string nom, EnumType type, int prix, int gain, std::vector<int> combinaisons)
    : Carte(id, nom, type, prix), combinaisons(combinaisons), gain(gain) {

}
