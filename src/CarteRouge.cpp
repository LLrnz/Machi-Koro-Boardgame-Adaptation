#include "./../headers/CarteRouge.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include <sstream>

CarteRouge::CarteRouge(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, int nbMonuToActivate)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur),nbMonuToActivate(nbMonuToActivate) {

}

int CarteRouge::getNbMonuToActivate() {
    return nbMonuToActivate;
}

void CarteRouge::activer(Joueur* joueurProprietaire){
    Jeu& jeu = Jeu::getJeu();
    string name = this->getNom();
    Joueur* joueurActif = jeu.getJoueurActif();
    Controleur* controleur = Controleur::getControleur();

    // id : 1 = Café, 2 = Restaurant, 3 = Pizzeria, 4 = Moonster burdcger, 5 = Bar a sushi
    // id : 6 = Club privé, 7 = Restaurant gastronomique

    int gain = this->getGain();
    if (this->getId() == 5 && !joueurProprietaire->hasPort()) {              // si c'est bar à sushi mais que le joueur n'a pas de port
        return;                                                                 // on ne fait rien et on sort de la fonction
    }
    else if (nbMonuToActivate != 0 ) {                                      // si la carte a un nombre de monument requis
        int compteur = 0;
        for (size_t i = 0; i < size(joueurActif->getMonuments()); i++) {     // pour chaque monument du joueur actif
            if (joueurActif->getMonuments()[i]->getConstruit() == true)           // si le monument est construit
                compteur += 1;                                                      // on incremente le compteur
        }
        if (compteur < this->getNbMonuToActivate()) {                       // si le joueur n'a pas assez de monument construit
            return;                                                             // on ne fait rien et on sort de la fonction
        }
        gain = this->getId() == 6 ? joueurActif->getPieces() : gain; // si c'est un club prive, le gain est le nombre de pieces du joueur actif
    }

    joueurActif->perdrePieces(gain);           // le joueur actif perd des pieces
    joueurProprietaire->gagnerPieces(gain);                          // le joueur proprietaire gagne des pieces

    // affichage
    stringstream s;
    s << joueurActif->getPseudo() << " a paye " << gain << " pieces a " << joueurProprietaire->getPseudo() << endl;
    controleur->afficher(s.str());
}

std::string CarteRouge::to_string() const {
    std::string res = "[" + this->getNom() + "] ~" +std::to_string(this->getPrix()) + "p~ : vole <" + std::to_string(this->getGain()) + "> pièces au joueur actif s'il a au moins " + std::to_string(this->nbMonuToActivate) + " monuments construits. S'active sur (" ;
    for(const auto &i : this->getCombinaisons()){
        res += std::to_string(i);
        res += ", ";
    }
    res += ") aux dés.";
    return res;
}
