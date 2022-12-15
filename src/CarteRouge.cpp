#include "./../headers/CarteRouge.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"

CarteRouge::CarteRouge(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur) {

}
void CarteRouge::activer(Joueur joueurProprietaire){
    string name = this->getNom();
    Joueur joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur* controleur = Controleur::getControleur();
    
    if (name == "Café" || name == "Restaurant" || name == "Pizzeria" || name == "Moonster burger"){
        int payement = joueurActif.perdrePieces(this->getGain());
        joueurProprietaire.gagnerPieces(payement);
        controleur->afficher(joueurActif.getPseudo());
        controleur->afficher("a paye ");
        controleur->afficher(payement);
        controleur->afficher(" pieces a ");
        controleur->afficher(joueurProprietaire.getPseudo());
        controleur->afficher("\n");
    } 
    if (name == "Bar a sushi"){
        Joueur joueurActif = Jeu::getJeu().getJoueurActif();
        if (joueurActif.hasPort()){
            int payement = joueurActif.perdrePieces(4);
            joueurProprietaire.gagnerPieces(payement);
            controleur->afficher(joueurActif.getPseudo());
            controleur->afficher("a paye ");
            controleur->afficher(payement);
            controleur->afficher(" pieces a ");
            controleur->afficher(joueurProprietaire.getPseudo());
            controleur->afficher("\n");
        }
    }
    if (name == "Restaurant 5 etoiles"){
        int compteur = 0;
        Joueur joueurActif = Jeu::getJeu().getJoueurActif();
        for (int i = 0; i<size(joueurActif.getMonuments());i++)
            if (joueurActif.getMonuments()[i].getConstruit() == true)
                compteur += 1;
        if (compteur >= 2){
            int payement = joueurActif.perdrePieces(5);
            joueurProprietaire.gagnerPieces(payement);   
            controleur->afficher(joueurActif.getPseudo());
            controleur->afficher("a paye ");
            controleur->afficher(payement);
            controleur->afficher(" pieces a ");
            controleur->afficher(joueurProprietaire.getPseudo());
            controleur->afficher("\n");
        }  
    }
    if (name == "Club prive"){
        int compteur = 0;
        Joueur joueurActif = Jeu::getJeu().getJoueurActif();
        for (int i = 0; i<size(joueurActif.getMonuments());i++)
            if (joueurActif.getMonuments()[i].getConstruit() == true)
                compteur += 1;
        if (compteur >= 3){
            int payement = joueurActif.getPieces();
            joueurProprietaire.gagnerPieces(payement);
            joueurActif.perdrePieces(payement);
            controleur->afficher(joueurActif.getPseudo());
            controleur->afficher("a paye ");
            controleur->afficher(payement);
            controleur->afficher(" pieces a ");
            controleur->afficher(joueurProprietaire.getPseudo());
            controleur->afficher("\n");
        }              
    }

}

