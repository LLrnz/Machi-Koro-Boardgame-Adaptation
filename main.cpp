#include <QtCore>
#include <iostream>
#include "headers/Controleur.h"



int main() {


    Controleur::getControleur()->nouvellePartie();
    Jeu::getJeu().afficherCartes();
    Controleur::getControleur()->afficher("a\n");
    Controleur::getControleur()->demarrer();
    return 0;
}
