#include "./../headers/CarteVerte.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include <sstream>

CarteVerte::CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur) {

}

void CarteVerte::activer(){
    Joueur joueurActif = Jeu::getJeu().getJoueurActif();
    string nomCarte = getNom();

    if (nomCarte == "Boulangerie" || nomCarte == "Superette"){
        joueurActif.gagnerPieces(getGain());
    }
    else if (nomCarte == "Usine de fromage"){
        int compteur = 0;
        for (auto it = joueurActif.getBatiments().begin(); it != joueurActif.getBatiments().end(); it++){
            if ((*it)->getType() == TypeBatiment::vache)
                compteur += 1;
            joueurActif.gagnerPieces(3*compteur);
        }
    }
    else if (nomCarte == "Magasin de meubles"){
        int compteur = 0;
        for (auto it = joueurActif.getBatiments().begin(); it != joueurActif.getBatiments().end(); it++){
            if ((*it)->getType() == TypeBatiment::ecrou)
                compteur += 1;
            joueurActif.gagnerPieces(3*compteur);
        }
    }
    else if (nomCarte == "Marché de fruits et légumes"){
        int compteur = 0;
        for (auto it = joueurActif.getBatiments().begin(); it != joueurActif.getBatiments().end(); it++){
            if ((*it)->getType() == TypeBatiment::ble)
                compteur += 1;
            joueurActif.gagnerPieces(2*compteur);
        }
    }
    else if (nomCarte == "Fleuriste"){
        int compteur = 0;
        for (auto it = joueurActif.getBatiments().begin(); it != joueurActif.getBatiments().end(); it++){
            if ((*it)->getNom() == "Champ de fleurs")
                compteur += 1;
            joueurActif.gagnerPieces(1*compteur);
        }
    }
    else if (nomCarte == "Halle de marché"){
        int compteur = 0;
        for (auto it = joueurActif.getBatiments().begin(); it != joueurActif.getBatiments().end(); it++){
            if ((*it)->getType() == TypeBatiment::restaurant)
                compteur += 1;
            joueurActif.gagnerPieces(2*compteur);
        }
    }
    else if (nomCarte == "Epicerie"){
        int compteur = 0;
        Joueur joueurActif = Jeu::getJeu().getJoueurActif();
        for (int i = 0; i<size(joueurActif.getMonuments());i++)
            if (joueurActif.getMonuments()[i].getConstruit() == true)
                compteur += 1;
        if (compteur < 2)
            joueurActif.gagnerPieces(5);
    }
    else if (nomCarte == "Entreprise de travaux publics"){
        std::vector<string> monumentsConstruits;
        for (auto i = joueurActif.getMonuments().begin(); i != joueurActif.getMonuments().end() ; i++)
            if ((*i).getConstruit() == true)
                monumentsConstruits.push_back((*i).getNom());

        if (!monumentsConstruits.empty()){
            Controleur::getControleur()->afficher("Vous devez retourner une de vos cartes monuments sur sa face travaux : \n");
            stringstream s;
            for (auto i = monumentsConstruits.begin(); i != monumentsConstruits.end() ; i++){
                s << "-" << *i << ")\n";
                Controleur::getControleur()->afficher(s.str());
            }
            Controleur::getControleur()->afficher("Quel batiment voulez vous mettre en travaux : ");
            string choix = Controleur::getControleur()->lire();

            for (auto i = joueurActif.getMonuments().begin(); i != joueurActif.getMonuments().end() ; i++)
                if ((*i).getNom() == choix)
                    (*i).detruit();

        }
    }
    else if (nomCarte == "Moonster soda"){
        int compteur = 0;
        for (auto i = Jeu::getJeu().getJoueurs().begin() ; i != Jeu::getJeu().getJoueurs().end() ; i++ ){
            for (auto j = (*i).getBatiments().begin() ; j != (*i).getBatiments().end() ; j++){
                if ((*j)->getType()==TypeBatiment::restaurant)
                    compteur++;
            }
        }
        joueurActif.gagnerPieces(compteur);
    }
    else if (nomCarte == "Entreprise de déménagement"){
        stringstream s;
        int n=0;
        Controleur::getControleur()->afficher("Liste des cartes possibles à déménager : \n");
        for (auto i = joueurActif.getBatiments().begin(); i != joueurActif.getBatiments().end() ; i++){
            if ((*i)->getType()!=TypeBatiment::special){
                s << "-" << (*i)->getNom() << " (" << n++ << ")\n";
                Controleur::getControleur()->afficher(s.str());
            }
        }
        Controleur::getControleur()->afficher("Votre choix : ");
        int choix = std::stoi(Controleur::getControleur()->lire());
        bool demenagement = false;
        n = 0;
        for (auto i = joueurActif.getBatiments().begin(); demenagement && i != joueurActif.getBatiments().end() ; i++){
            if ((*i)->getType()!=TypeBatiment::special){
                if (n++==choix) {
                    //Echange avec le joueur à choisir
                    Controleur::getControleur()->afficher("Chez qui voulez vous déménager : \n");
                    for (auto j = Jeu::getJeu().getJoueurs().begin() ; j != Jeu::getJeu().getJoueurs().end() ; j++){

                    }
                    demenagement = true;

                }
            }
        }
    }
}
