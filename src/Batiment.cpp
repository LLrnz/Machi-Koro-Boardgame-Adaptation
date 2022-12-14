#include "../headers/Batiment.h"

Batiment::Batiment(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons)
    : Carte(id, nom, prix), type:type, combinaisons(combinaisons), gain(gain) {

}
