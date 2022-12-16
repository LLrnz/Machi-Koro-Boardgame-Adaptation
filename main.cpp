#include <QtCore>
#include <iostream>
#include "src/Jeu.cpp"


int main() {


    Controleur::getControleur()->nouvellePartie();
    Jeu::getJeu().afficherCartes();


    return 0;
}
