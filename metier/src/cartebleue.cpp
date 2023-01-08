#include "../headers/CarteBleue.h"
#include "../headers/Controleur.h"
#include <sstream>

CarteBleue::CarteBleue(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur) {
}

void CarteBleue::activer(Joueur* joueurProprietaire) {
    string name = this->getNom();
    Controleur *controleur = Controleur::getControleur();

    // id : champ de blé = 1, ferme = 2, forêt = 3, mine = 4,
    // verger de pommiers = 5, vignoble = 6, petit bateau de pêche = 7, chalutier = 8


    controleur->afficher(joueurProprietaire->getPseudo() + " a activé la carte bleue " + this->getNom() +"\n");

    int gain = this->getGain();


    //À promptement déplacer dans une classe PetitBateauDePêche qui hérite de carte bleu
    if (this->getId() == 8){
        if(joueurProprietaire->hasPort()) { // si c'est un chalutier et que le joueur a un bateau de pêche
            int de1 = (rand()%6)+1;
            int de2 = (rand()%6)+1;
            int resultatJet = de1 + de2;

            gain = resultatJet;

            controleur->afficher("Le résultat du jet de dé lié au chalutier est " + std::to_string(resultatJet) + "\n");
        }else{ //si le joueur n'a pas le port pour activer le petit bateau de pêche.
            gain = 0;
        }
    }

//    if ((this->getId() == 7 || this->getId() == 8) && !joueurProprietaire->hasPort()) { // si c'est un petit bateau de pêche ou un chalutier et que le joueur actif n'a pas de port
//        return;
//    }

    joueurProprietaire->gagnerPieces(gain);
    controleur->afficher(joueurProprietaire->getPseudo() + " gagne " + std::to_string(gain) + "\n");
}

std::string CarteBleue::to_string() const {
    std::string res = "[" + this->getNom() + "] " +std::to_string(this->getPrix()) + " : produit <" + std::to_string(this->getGain()) + "> pièces sur (" ;
    for(const auto &i : this->getCombinaisons()){
        res += std::to_string(i);
        res += ",";
    }
    res += ") aux dés.";
    return res;
}


