#include <QtCore>
#include <iostream>
#include "src/Jeu.cpp"
#include "headers/Monument.h"


int main() {


    Controleur::getControleur()->nouvellePartie();
    Jeu::getJeu().afficherCartes();
    Controleur::getControleur()->afficher("a");
    Controleur::getControleur()->demarrer();
    return 0;
}
