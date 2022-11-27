#include "./../headers/CarteBleue.h"

CarteBleue::CarteBleue(int id, std::string nom, EnumType type, int prix, int gain, std::vector<int> combinaisons)
    : Batiment(id, nom, type, prix, gain, combinaisons) {

}
