#include <QtCore>
#include <iostream>
#include "src/Jeu.cpp"


int main() {

    Jeu& j = Jeu::getJeu();

    j.afficherCartes();


    return 0;
}
