#include "./../headers/CarteViolette.h"
#include "./../headers/enums.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include <cmath>
#include <sstream>

CarteViolette::CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur){

}
void CarteViolette::activer(Joueur joueurProprietaire){
    string          name        = this->getNom();
    Joueur          joueurActif = Jeu::getJeu()->getJoueurActif();
    Controleur*     controleur  = Controleur::getControleur();
    vector<Joueur>  joueurs     = Jeu::getJeu()->getJoueurs();

    // id : Stade = 1, Chaine TV = 2, Centre des Affaires = 3
    // id : Maison d'édition = 4, Centre des impots = 5

    stringstream s;

    s << "La carte violette " << name << " est activée \n";
    controleur->afficher(s.str());

    if (this->getId() == 1){    // si c'est le stade
        vector<Joueur> joueurs = Jeu::getJeu()->getJoueurs();
        for (size_t i = 0 ; i < sizeof(joueurs) ; i++){
            if (i != Jeu::getJeu()->getIndiceJoueurActif()){
                Jeu::getJeu()->getJoueurActif().gagnerPieces(joueurs[i].perdrePieces(this->getGain()));
                stringstream s;
                s << "Vous avez pris " << this->getGain()" pieces a " << joueurs[i].getPseudo() << "\n";
                controleur->afficher(s.str());
            }
        }
    }
    if (this->getId() == 2){    // si c'est la chaine TV
        vector<Joueur> joueurs = Jeu::getJeu()->getJoueurs();
        s << "A qui voulez vous prendre" << this->getGain() << "pieces ? \n";
        controleur->afficher(s.str());
        for (size_t i = 0; i < sizeof(joueurs) ; i++){
            stringstream s;
            s << i << " : " << joueurs[i].getPseudo() << " qui possede " << joueurs[i].getPieces() << " pieces \n";
            controleur->afficher(s.str());
        }
        string reponse = controleur->lire_str();
        Jeu::getJeu()->getJoueurActif().gagnerPieces(joueurs[std::stoi(reponse)].perdrePieces(5));
    }
    if (this->getId() == 3){    // si c'est le centre des affaires
        //Affichage et selection de la personne avec qui échange run batiment
        stringstream s;
        s << "Avec qui voulez vous echanger un etablissement ? \n";
        s << "-1 : Personne \n";
        controleur->afficher(s.str());
        for (size_t i = 0; i<sizeof(joueurs);i++){
            stringstream s;
            s << i << " : " << joueurs[i].getPseudo() << " qui possede : ";;
            controleur->afficher(" qui possede : ");
            for (size_t j = 0; j<sizeof(joueurs[i].getConstructions());j++){
                s << joueurs[i].getConstructions()[j]->getNom() << " ";
            }
            controleur->afficher(s.str());
        }
        int reponse = std::stoi(controleur->lire_str());
        bool confirmeEchange = response == -1 ? false : true; //Si -1 alors pas d'échange

        //Séquence d'échange
        if (confirmeEchange){
            //Affichage et selection de la carte a prendre chez l'adversaire (ou vous même)
            stringstream s;
            s << "Choisisez la carte a prendre depuis chez " << joueurs[reponse].getPseudo() << "\n";
            for (size_t k = 0; k<sizeof(joueurs[reponse].getConstructions());k++){
                if (joueurActif.getConstructions()[k]->getType()!=TypeBatiment::special){
                    s << k << " : " << joueurs[reponse].getConstructions()[k]->getNom() << " ";
                }
            }
            controleur->afficher(s.str());
            int repPrendre = std::stoi(controleur->lire_str());
            stringstream s;
            s << "Choisisez la carte a echanger depuis chez vous" << joueurActif.getPseudo() << "\n";
            for (size_t m = 0; m<sizeof(joueurActif.getConstructions());m++){
                if (joueurActif.getConstructions()[m]->getType()!=TypeBatiment::special){
                    s << m << " : " << joueurActif.getConstructions()[m]->getNom() << " ";
                }
            }
            controleur->afficher(s->str());
            int repEchange = std::stoi(controleur->lire_str());
            Batiment* ptTempPrendre = joueurs[reponse].getConstructions()[repPrendre];
            Batiment* ptTempEchange = joueurActif.getConstructions()[repEchange];
            joueurActif.ajouterBatiment(ptTempPrendre);
            joueurs[reponse].ajouterBatiment(ptTempEchange);
            joueurActif.enleverBatimentParIndice(repEchange);
            joueurs[reponse].enleverBatimentParIndice(repPrendre);
        }
    }
    if (this->getId() == 4){    // si c'est la maison d'édition
        int compteur = 0;
        for (size_t i =0; i<sizeof(joueurs);i++){
            compteur = 0;
            for (size_t j; j<sizeof(joueurs[i].getConstructions());j++) {
                if (joueurs[i].getConstructions()[j]->getType() == TypeBatiment::magasin || joueurs[i].getConstructions()[j]->getType() == TypeBatiment::restaurant)
                    compteur+=1;
                joueurActif.gagnerPieces(joueurs[i].perdrePieces(compteur));
                stringstream s;
                s << "Vous avez pris " << compteur << " pieces a " << joueurs[i].getPseudo() << "\n";
                controleur->afficher(s.str());
            }
        }
    }
    if (this->getId() == 5){    // si c'est le centre des impots
        for (size_t i =0; i<sizeof(joueurs);i++){
            if (joueurs[i].getPieces()>=10) {
                int gain = floor(joueurs[i].getPieces()/2);
                joueurActif.gagnerPieces(joueurs[i].perdrePieces(gain));
                stringstream s;
                s << "Vous avez pris " << gain << " pieces a " << joueurs[i].getPseudo() << "\n";
                controleur->afficher(s.str());
            }
        }
    }
}
