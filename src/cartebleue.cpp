#include "../headers/CarteBleue.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"

CarteBleue::CarteBleue(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    :Batiment(id, nom, type, prix, gain, combinaisons, couleur) {

}
void CarteBleue::activer(Joueur joueurProprietaire){
    string name = this->getNom();
    Joueur joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur* controleur = Controleur::getControleur();
    if (name == "Champs de blé" || name == "Ferme" || name == "Forêt" || name == "Mine" || name == "Verger de Pommiers" || name == "Vignoble" || name == "Champ de fleurs"){
        joueurProprietaire.gagnerPieces(this->getGain());
        controleur->afficher(joueurProprietaire.getPseudo());
        controleur->afficher("a gagne ");
        controleur->afficher(this->getGain());
        controleur->afficher(" pieces grace a son/sa ");
        controleur->afficher(name);
        controleur->afficher("\n");

    }
    if(name == "Petit bateau de pêche"){
        if (joueurProprietaire.hasPort()){
            joueurProprietaire.gagnerPieces(this->getGain());
            controleur->afficher(joueurProprietaire.getPseudo());
            controleur->afficher("a gagne ");
            controleur->afficher(this->getGain());
            controleur->afficher(" pieces grace a son/sa ");
            controleur->afficher(name);
            controleur->afficher("\n");
        }
    }
    if(name == "Chalutier"){
        if (joueurProprietaire.hasPort()){
            int de1 = rand() % 6;
		    int de2 = rand() % 6;
            int resultatJet = de1 + de2;
            joueurProprietaire.gagnerPieces(resultatJet);
            controleur->afficher("Le resultat du jet de de lie au chalutier est ");
            controleur->afficher(resultatJet);
            controleur->afficher("\n");
            controleur->afficher(joueurProprietaire.getPseudo());
            controleur->afficher("a donc gagne ");
            controleur->afficher(resultatJet);
            controleur->afficher("\n");
        }
    }
}
