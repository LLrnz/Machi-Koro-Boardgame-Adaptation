#include <QtCore>
#include <iostream>
#include "src/Jeu.cpp"
#include "headers/Monument.h"


int main() {

    Jeu& j = Jeu::getJeu();

    j.afficherCartes();

    return 0;
}
