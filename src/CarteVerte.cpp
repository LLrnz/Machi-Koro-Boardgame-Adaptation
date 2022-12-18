#include "./../headers/CarteVerte.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include <sstream>

CarteVerte::CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur), effectType(effectType){}


void CarteVerte::activer(Joueur* joueurProprietaire){
    Joueur* joueurActif = Jeu::getJeu().getJoueurActif();
    vector<Joueur> joueurs = Jeu::getJeu().getJoueurs();
    string nomCarte = getNom();
    int idCarte = getId();

    int gain = this->getGain();
    int compteur = 0;
    stringstream s; // il faut mettre en place la mise à jour du flux dans chaque partie du if

    // id : Boulangerie = 1, Superette = 2, Usine de fromage = 3, Magasin de meubles = 4, Marché de fruits et légumes = 5
    // id: Fleuriste = 6, Halle de marché = 7, Epicerie = 8, Entreprise de travaux publics = 9
    // id : Moonster soda = 10, Entreprise de déménagement = 11

    //IMMONDE il faut faire de l'héritage !!
    if (this->getEffectType() != TypeBatiment::none){                                                       // si la carte a un effetType
        if (idCarte == 10){                                                                                     // si c'est Moonster soda
            for (auto &i : Jeu::getJeu().getJoueurs()){          // pour chaque joueur
                for (auto &j : i.getConstructions()){                // pour chaque batiment du joueur
                    if (j->getType() == getEffectType())                                                                 // si le batiment est du type de l'effet
                        compteur++;
                }
            }
            gain = compteur;
        }
        else {                                                                                             // si ce n'est pas Moonster soda
            for (auto &it : joueurActif->getConstructions()){ // pour chaque batiment du joueur actif
                if (it->getType() == getEffectType()){                                                              // si le batiment est du type de l'effet
                    compteur ++;
                }
                if(compteur == 0) compteur =1;
                gain = this->getGain() * compteur;
            }
        }
    }
    else {
        switch(idCarte){


            case 8: //Epicerie
                if (joueurActif->getNbMonumentsConstruits() >= 2){                                                                               // si le joueur a construit au moins 2 monuments
                    gain = 0;                                                                                           // il ne gagne rien
                }
            break;


            case 6: //Fleuriste
                for (auto &it : joueurActif->getConstructions()){   // pour chaque batiment du joueur actif
                    if (it->getId() == 9)                                                            // si le batiment est un champ de fleurs (voir CarteBleue.cpp)
                        compteur += 1;
                    gain = compteur;
                }
            break;


            case 9: {//Entreprise de travaux publics
                    vector<Monument*> monumentsVendables;
                    Controleur::getControleur()->afficher("Liste des monuments construits : \n");
                    for (auto &monu : joueurProprietaire->getMonuments()){
                        if (monu->getConstruit()){
                            monumentsVendables.push_back(monu);
                        }
                    }


                    if (!monumentsVendables.empty()){
                        Controleur::getControleur()->afficher("Choisisez le monument à detruire pour gagner 8 pièces \n");
                        Monument* reponse = Controleur::getControleur()->selection_monument(monumentsVendables);
                        reponse->detruire();
                        gain = 8;
                    }
                    else {
                        Controleur::getControleur()->afficher("Vous n'avez aucun monument à vendre \n");
                        gain = 0;
                    }
                }
            break;


            case 11: //Entreprise de déménagement

                Controleur::getControleur()->afficher("Liste des cartes possibles à déménager : \n");     // on affiche les cartes possibles à déménager
                vector<Batiment*> choixBatiments;
                for (auto &b : joueurActif->getConstructions()){  // pour chaque batiment du joueur actif
                    if (b->getType()!=TypeBatiment::special)
                        choixBatiments.push_back(b);
                }

                Controleur::getControleur()->afficher("Votre choix : \n");
                Batiment* batimentChoisi = Controleur::getControleur()->selection_batiment(choixBatiments);

                Controleur::getControleur()->afficher("Choisisez un AUTRE joueur à qui gracieusement donner cette carte \n");
                //On peut choisir tous les joueurs sauf le joueur actif

                Joueur* joueurChoisi = Controleur::getControleur()->selection_joueur(Jeu::getJeu().getJoueursSansActifPtr());

                joueurChoisi->ajouterBatiment(batimentChoisi);
                joueurProprietaire->enleverBatiment(batimentChoisi);
                gain = 4;
            break;

        }

    }
    Controleur::getControleur()->afficher(this->getNom() + " vous a rapporté " + std::to_string(gain) + " pièces.\n");
    joueurActif->gagnerPieces(gain);
}


std::string CarteVerte::to_string() const {
    std::string res = "[" + this->getNom() + "] \e[0;93m" +std::to_string(this->getPrix()) + "p\e[0m : produit <" + std::to_string(this->getGain()) + "> pièces sur (" ;
    for(const auto &i : this->getCombinaisons()){
        res += std::to_string(i);
        res += ", ";
    }
    res += ") aux dés, ";

    switch(getId()){
        case 10: //Moonster soda
            res += "gagnez le gain pour chaque carte restaurant construite.";
        break;


        case 8: //Epicerie
            res += "gagnez le gain si vous avez moins de 2 monuments construits";
        break;


        case 6: //Fleuriste
           res += "pour chaque carte Jardin de fleur construite.";
        break;


        case 9: //Entreprise de travaux publics
            res += "Détruisez un monument pour gagner 8 pièces.";
        break;


        case 11: //Entreprise de déménagement
            res += "vous gagnez les pièces en donnant un de vos batiments non spécial à un autre joueur.";
        break;

    }

    return res;
}
