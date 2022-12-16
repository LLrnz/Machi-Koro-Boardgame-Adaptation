#pragma once
#include <string>
#include "../headers/enums.h"

TypeBatiment determineType(std::string s) {
    TypeBatiment type;
    if (s == "ble") {
        type = TypeBatiment::ble;
    }
    else if (s == "vache") {
        type = TypeBatiment::vache;
    }
    else if (s == "ecrou") {
        type = TypeBatiment::ecrou;
    }
    else if (s == "fruit") {
        type = TypeBatiment::fruit;
    }
    else if (s == "magasin") {
        type = TypeBatiment::magasin;
    }
    else if (s == "usine") {
        type = TypeBatiment::usine;
    }
    else if (s == "restaurant") {
        type = TypeBatiment::restaurant;
    }
    else {
        type = TypeBatiment::special;
    }
    return type;
}

/*Source determineSource(std::string s) {
    Source source;
    if (s == "tous_les_joueurs") {
        source = Source::tous_les_joueurs;
    }
    else {
        source = Source::choix_joueur;
    }
    return source;
}*/
