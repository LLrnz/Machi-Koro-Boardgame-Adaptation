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
    if ((this->getId() == 7 || this->getId() == 8) && !joueurProprietaire->hasPort()) { // si c'est un petit bateau de pêche ou un chalutier et que le joueur actif n'a pas de port
        return;
    }

    stringstream s;
    s << "Le joueur " << joueurProprietaire->getPseudo() << " a active la carte bleue " << this->getNom() << endl;

    int gain = this->getGain();

    if (this->getId() == 8) { // si c'est un chalutier
        int de1 = rand() % 6;
        int de2 = rand() % 6;
        int resultatJet = de1 + de2;

        gain = resultatJet;

        s << "Le résultat du jet de de lie au chalutier est " << resultatJet << endl;
        s << joueurProprietaire->getPseudo() << "a donc gagne " << resultatJet << endl;
    }

    joueurProprietaire->gagnerPieces(gain);

    controleur->afficher(s.str());
}

std::string CarteBleue::to_string() const {
    std::string res = "[" + this->getNom() + "] : produit <" + std::to_string(this->getGain()) + "> pièces sur (" ;
    for(const auto &i : this->getCombinaisons()){
        res += std::to_string(i);
        res += ", ";
    }
    res += ") aux dés.";
    return res;
}


