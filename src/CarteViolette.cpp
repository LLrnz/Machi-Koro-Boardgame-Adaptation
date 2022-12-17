#include "./../headers/CarteViolette.h"
#include "./../headers/enums.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include <cmath>

CarteViolette::CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur){

}
void CarteViolette::activer(Joueur* joueurProprietaire){
    string name = this->getNom();
    Joueur* joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur* controleur = Controleur::getControleur();
    vector<Joueur> joueurs = Jeu::getJeu().getJoueurs();

    if (name == "Stade"){

        for (auto &j : joueurs){
            if (&j != joueurActif){
                joueurActif->gagnerPieces(j.perdrePieces(2));
            }
        }
    }
    if (name == "Chaine TV"){
        controleur->afficher("A qui voulez vous prendre 5 pieces ? \n");

        vector<Joueur*> choixJoueurs;
        for(auto &j : joueurs){
            if(&j != joueurActif)
            choixJoueurs.push_back(&j);
        }

        Joueur* joueurChoisi = controleur->selection_joueur(choixJoueurs);
        joueurActif->gagnerPieces(joueurChoisi->perdrePieces(5));
    }
    if (name == "Centre des Affaires"){
        //Affichage et selection de la personne avec qui échange run batiment
        controleur->afficher("Avec qui voulez vous echanger un etablissement ? \n");
        controleur->afficher("-1 : Personne \n");
        Joueur* joueurVise = controleur->selection_joueur_batiment(Jeu::getJeu().getJoueursSansActifPtr());


        //Si il choisis -1, il n'effectue pas d'échange
        //Séquence d'échange
        if (joueurVise != nullptr){
            //Affichage et selection de la carte a prendre chez l'adversaire (ou vous même)
            controleur->afficher("Choisisez la carte a prendre depuis chez ");
            controleur->afficher(joueurVise->getPseudo());
            controleur->afficher("\n");

            Batiment* repPrendre = controleur->selection_batiment(joueurVise->getConstructions());

            controleur->afficher("Choisisez la carte a echanger depuis chez vous");
            controleur->afficher(joueurActif->getPseudo());
            controleur->afficher("\n");

            Batiment* repEchange = controleur->selection_batiment(joueurActif->getConstructions());


            joueurActif->ajouterBatiment(repPrendre);
            joueurVise->ajouterBatiment(repEchange);
            joueurActif->enleverBatiment(repEchange);
            joueurVise->enleverBatiment(repPrendre);
        }else{
            controleur->afficher("Echange annulé./n");
        }
    }
    if (name == "Maison d'édition"){
        int compteur = 0;
        for (auto &j : joueurs){
            compteur = 0;
            for (auto &b : j.getConstructions())
                if (b->getType() == TypeBatiment::magasin || b->getType() == TypeBatiment::restaurant)
                    compteur+=1;
            joueurActif->gagnerPieces(j.perdrePieces(compteur));
        }
    }
    if (name == "Centre des impots"){
        for (auto &j : joueurs){
            if (j.getPieces()>=10)
                joueurActif->gagnerPieces(j.perdrePieces(floor(j.getPieces()/2)));
        }
    }
}

std::string CarteViolette::to_string() const {
    std::string res = "[" + this->getNom() + "] : produit <" + std::to_string(this->getGain()) + "> pièces sur (" ;
    for(const auto &i : this->getCombinaisons()){
        res += std::to_string(i);
        res += ", ";
    }
    res += ") aux dés, ";

    switch(getId()){
        case 13: //stade
            res += "Insérer effet";
        break;


        case 14: //chaineTV
            res += "Insérer effet";
        break;


        case 15: //centreAffaires
           res += "Insérer effet";
        break;


    }

    return res;
}
