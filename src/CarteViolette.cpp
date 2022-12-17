#include "./../headers/CarteViolette.h"
#include "./../headers/enums.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include <cmath>
#include <sstream>

CarteViolette::CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur){

}

void CarteViolette::activer(Joueur* joueurProprietaire) {
    Jeu& jeu = Jeu::getJeu();
    string          name        = this->getNom();
    Controleur*     controleur  = Controleur::getControleur();
    vector<Joueur>  joueurs     = jeu.getJoueurs();
    Joueur*         joueurActif = jeu.getJoueurActif();

    // id : Stade = 1, Chaine TV = 2, Centre des Affaires = 3
    // id : Maison d'édition = 4, Centre des impots = 5

    stringstream s;

    s << "La carte violette " << name << " est activée \n";
    controleur->afficher(s.str());

    if (this->getId() == 1){    // si c'est le stade
        for (auto &j : joueurs){
            if (&j != joueurActif){
                joueurActif->gagnerPieces(j.perdrePieces(2));
            }
        }
    }
    if (this->getId() == 2){    // si c'est la chaine TV
        vector<Joueur> joueurs = jeu.getJoueurs();
        s << "A qui voulez vous prendre" << this->getGain() << "pieces ? \n";
        controleur->afficher(s.str());

        vector<Joueur*> choixJoueurs;
        for(auto &j : joueurs){
            if(&j != joueurActif)
            choixJoueurs.push_back(&j);
        }

        Joueur* joueurChoisi = controleur->selection_joueur(choixJoueurs);
        joueurActif->gagnerPieces(joueurChoisi->perdrePieces(5));
    }
    if (this->getId() == 3){    // si c'est le centre des affaires
        //Affichage et selection de la personne avec qui échange run batiment
        stringstream s;
        s << "Avec qui voulez vous echanger un etablissement ? \n";
        s << "-1 : Personne \n";
        controleur->afficher(s.str());
        Joueur* joueurVise = controleur->selection_joueur_batiment(jeu.getJoueursSansActifPtr());
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
    if (this->getId() == 4){    // si c'est la maison d'édition
        int compteur = 0;
        for (auto &j : joueurs){
            compteur = 0;
            for (auto &b : j.getConstructions())
                if (b->getType() == TypeBatiment::magasin || b->getType() == TypeBatiment::restaurant)
                    compteur+=1;
            joueurActif->gagnerPieces(j.perdrePieces(compteur));
        }
    }
    if (this->getId() == 5){    // si c'est le centre des impots
            for (size_t i =0; i<sizeof(joueurs);i++){
                if (joueurs[i].getPieces()>=10) {
                    int gain = floor(joueurs[i].getPieces()/2);
                    joueurActif->gagnerPieces(joueurs[i].perdrePieces(gain));
                    stringstream s;
                    s << "Vous avez pris " << gain << " pieces a " << joueurs[i].getPseudo() << "\n";
                    controleur->afficher(s.str());
                }
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
