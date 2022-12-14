#include <QtCore>
#include <iostream>
#include "src/Jeu.cpp"
#include "headers/Monument.h"


int main() {

    Jeu& j = Jeu::getJeu();

    j.afficherCartes();
    Monument m("Gare");
    Joueur j1("Lucas",TypeJoueur::humain);

    return 0;
}
