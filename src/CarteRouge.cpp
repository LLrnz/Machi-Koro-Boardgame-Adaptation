#include "./../headers/CarteRouge.h"
#include "../headers/Jeu.h"

CarteRouge::CarteRouge(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur) {

}
void CarteRouge::activer(Joueur joueurProprietaire){
    string name = this->getNom();
    Joueur joueurActif = Jeu::getJeu().getJoueurActif();
    
    if (name == "Café" || name == "Restaurant" || name == "Pizzeria" || name == "Moonster burger"){
        joueurProprietaire.gagnerPieces(joueurActif.perdrePieces(this->getGain()));
    } 
    if (name == "Bar a sushi"){
        int compteur = 0;
        Joueur joueurActif = Jeu::getJeu().getJoueurActif();
        if (joueurActif.hasPort())
            joueurProprietaire.gagnerPieces(joueurActif.perdrePieces(4));
    }
    if (name == "Restaurant  etoiles"){
        int compteur = 0;
        Joueur joueurActif = Jeu::getJeu().getJoueurActif();
        for (int i = 0; i<size(joueurActif.getMonuments());i++)
            if (joueurActif.getMonuments()[i].getConstruit() == true)
                compteur += 1;
        if (compteur >= 2)
            joueurProprietaire.gagnerPieces(joueurActif.perdrePieces(5));     
    }
    if (name == "Club prive"){
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
    
}

