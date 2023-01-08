#include <QtCore>
#include <iostream>
#include "metier/headers/Controleur.h"

// utile pour CP_UTF8 plus bas
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8); // permet l'affichage des accents dans la console
    
    Controleur::getControleur()->nouvellePartie();
    Jeu::getJeu().afficherCartes();
    Controleur::getControleur()->afficher("\n");
    Controleur::getControleur()->demarrer();
    return 0;
}
