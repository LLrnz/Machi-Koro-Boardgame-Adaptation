#include "./../headers/CarteRouge.h"

CarteRouge::CarteRouge(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons)
    : Batiment(id, nom, type, prix, gain, combinaisons) {

}
