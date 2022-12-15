#include "headers/Jeu.h"
#include "headers/CarteBleue.h"
#include "headers/CarteRouge.h"
#include "headers/CarteVerte.h"
#include "headers/CarteViolette.h"
#include "headers/Controleur.h"
#include "headers/Joueur.h"
#include "services.cpp"
#include <iostream>
#include <cstdlib> 

void activerRestaurant5Etoiles(Joueur joueurProprietaire){
    int compteur = 0;
    Joueur joueurActif = Jeu::getJeu().getJoueurActif();
    for (int i = 0; i<size(joueurActif.getMonuments());i++)
        if (joueurActif.getMonuments()[i].getConstruit() == true)
            compteur += 1;
    if (compteur >= 2){
        joueurProprietaire.gagnerPieces(joueurActif.perdrePieces(5));
    }              
}
void activerClubPrive(Joueur joueurProprietaire){
    int compteur = 0;
    Joueur joueurActif = Jeu::getJeu().getJoueurActif();
    for (int i = 0; i<size(joueurActif.getMonuments());i++)
        if (joueurActif.getMonuments()[i].getConstruit() == true)
            compteur += 1;
    if (compteur >= 3){
        joueurProprietaire.gagnerPieces(joueurActif.getPieces());
        joueurActif.perdrePieces(joueurActif.getPieces());
    }              
}
void activerBarShushi(Joueur joueurProprietaire){
    int compteur = 0;
    Joueur joueurActif = Jeu::getJeu().getJoueurActif();
    if (joueurActif.hasPort()){
        joueurProprietaire.gagnerPieces(joueurActif.perdrePieces(4));
    }              
}
void activerChaineDeTelevision(Joueur joueurProprietaire){
    
}
