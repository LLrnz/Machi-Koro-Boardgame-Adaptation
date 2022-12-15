#include "./../headers/CarteViolette.h"
#include "./../headers/enums.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"

CarteViolette::CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, Source source)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur), source(source) {

}
void CarteViolette::activer(Joueur joueurProprietaire){
    string name = this->getNom();
    Joueur joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur* controleur = Controleur::getControleur();

    if (name == "Stade"){
        vector<Joueur> joueurs = Jeu::getJeu().getJoueurs();
        for (size_t i =0; i<sizeof(joueurs);i++){
            if (i != Jeu::getJeu().getIndiceJoueurActif()){
                Jeu::getJeu().getJoueurActif().gagnerPieces(joueurs[i].perdrePieces(2));
            }
        }
    }
    if (name == "Chaine TV"){
        vector<Joueur> joueurs = Jeu::getJeu().getJoueurs();
        controleur->afficher("A qui voulez vous prendre 5 pieces ? \n");
        for (size_t i=0; i<sizeof(joueurs);i++){
            controleur->afficher(i);
            controleur->afficher(" : ");
            controleur->afficher(joueurs[i].getPseudo());
            controleur->afficher(" qui possede ");
            controleur->afficher(joueurs[i].getPieces());
            controleur->afficher(" pieces \n ");
        }
        string reponse = controleur->lire();
        Jeu::getJeu().getJoueurActif().gagnerPieces(joueurs[std::stoi(reponse)].perdrePieces(5));
    }
    if (name == "Centre des Affaires"){
        vector<Joueur> joueurs = Jeu::getJeu().getJoueurs();
        //Affichage et selection de la personne avec qui échange run batiment
        controleur->afficher("Avec qui voulez vous echanger un etablissement ? \n");
        controleur->afficher("-1 : Personne \n");
        for (size_t i=0; i<sizeof(joueurs);i++){
            controleur->afficher(i);
            controleur->afficher(" : ");
            controleur->afficher(joueurs[i].getPseudo());
            controleur->afficher(" qui possede : ");
            for (size_t j = 0; j<sizeof(joueurs[i].getConstructions());j++){
                controleur->afficher(joueurs[i].getConstructions()[j]->getNom());
                controleur->afficher(" ");
            }
            controleur->afficher("\n");
        }
        int reponse = std::stoi(controleur->lire());
        bool confirmeEchange = false;
        //Si il choisis -1, il n'effectue pas d'échange
        if (reponse != -1)
            confirmeEchange = true;
        //Séquence d'échange
        if (confirmeEchange){
            //Affichage et selection de la carte a prendre chez l'adversaire (ou vous même)
            controleur->afficher("Choisisez la carte a prendre depuis chez ");
            controleur->afficher(joueurs[reponse].getPseudo());
            controleur->afficher("\n");
            for (size_t k = 0; k<sizeof(joueurs[reponse].getConstructions());k++){
                if (joueurActif.getConstructions()[k]->getType()!=TypeBatiment::special){
                    controleur->afficher(k);
                    controleur->afficher(" : ");
                    controleur->afficher(joueurs[reponse].getConstructions()[k]->getNom());
                    controleur->afficher(" ");
                }
            }
            int repPrendre = std::stoi(controleur->lire());
            controleur->afficher("Choisisez la carte a echanger depuis chez vous");
            controleur->afficher(joueurActif.getPseudo());
            controleur->afficher("\n");
            for (size_t m = 0; m<sizeof(joueurActif.getConstructions());m++){
                if (joueurActif.getConstructions()[m]->getType()!=TypeBatiment::special){
                    controleur->afficher(m);
                    controleur->afficher(" : ");
                    controleur->afficher(joueurActif.getConstructions()[m]->getNom());
                    controleur->afficher(" ");
                }
            }
            controleur->afficher("\n");
            int repEchange = std::stoi(controleur->lire());
            Batiment* ptTempPrendre = joueurs[reponse].getConstructions()[repPrendre];
            Batiment* ptTempEchange = joueurActif.getConstructions()[repEchange];
            joueurActif.getConstructions().push_back(ptTempPrendre);
            joueurs[reponse].getConstructions().push_back(ptTempEchange);
            joueurActif.getConstructions().erase(joueurActif.getConstructions().begin()+repEchange);
            joueurs[reponse].getConstructions().erase(joueurs[reponse].getConstructions().begin()+repPrendre);
        }
    }
    if (name == "Maison d'édition"){
        
    }
}