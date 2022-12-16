#include <QtCore>
#include <iostream>
#include "src/Jeu.cpp"
#include "headers/Monument.h"


int main() {

    Jeu& j = Jeu::getJeu();

    j.afficherCartes();
    Controleur::getControleur()->afficher("a");
    return 0;
}
