#include <QtCore>
#include <iostream>
#include "src/Jeu.cpp"


int main() {


    Controleur::getControleur()->nouvellePartie();
    Jeu::getJeu().afficherCartes();

    //Recap
    Controleur::getControleur()->afficher("Récap : ");
    Controleur::getControleur()->afficher(to_string(Controleur::getControleur()->getNbJoueurs()));
    Controleur::getControleur()->afficher("\n");
    Controleur::getControleur()->afficher(Controleur::getControleur()->getPseudo(0));
    Controleur::getControleur()->afficher("\n");
    Controleur::getControleur()->afficher(Controleur::getControleur()->getPseudo(1));

    return 0;
}
