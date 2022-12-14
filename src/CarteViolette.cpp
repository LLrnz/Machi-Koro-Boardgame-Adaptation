#include "./../headers/CarteViolette.h"
#include "./../headers/enums.h"

CarteViolette::CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Source source)
    : Batiment(id, nom, type, prix, gain, combinaisons), source(source) {

}
