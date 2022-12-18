#include "./../headers/CarteVerte.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include <sstream>

CarteVerte::CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur), effectType(effectType){}


void CarteVerte::activer(Joueur* joueurProprietaire){
    Jeu& jeu = Jeu::getJeu();
    Joueur* joueurActif = jeu.getJoueurActif();
    vector<Joueur> joueurs = jeu.getJoueurs();
    string nomCarte = getNom();
    int idCarte = getId();

    int gain = this->getGain();
    int compteur = 0;
    stringstream s; // il faut mettre en place la mise à jour du flux dans chaque partie du if

    // id : Boulangerie = 1, Superette = 2, Usine de fromage = 3, Magasin de meubles = 4, Marché de fruits et légumes = 5
    // id: Fleuriste = 6, Halle de marché = 7, Epicerie = 8, Entreprise de travaux publics = 9
    // id : Moonster soda = 10, Entreprise de déménagement = 11


    if (this->getEffectType() != TypeBatiment::none){                                                       // si la carte a un effetType
        if (idCarte == 10){                                                                                     // si c'est Moonster soda
            for (auto i = jeu.getJoueurs().begin(); i != jeu.getJoueurs().end(); i++){          // pour chaque joueur
                for (auto j = (*i).getConstructions().begin(); j != (*i).getConstructions().end(); j++){                // pour chaque batiment du joueur
                    if ((*j)->getType() == getEffectType())                                                                 // si le batiment est du type de l'effet
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
                int i = 0;
                Controleur::getControleur()->afficher("Liste des monuments construits : \n");
                for (Monument* &monu : joueurProprietaire->getMonuments()){
                    if (monu->getConstruit()){
                        monumentsVendables.push_back(monu);
                        s.str("");
                        s << "  " << i << " : " << monu->getNom() << ")\n";
                        Controleur::getControleur()->afficher(s.str());
                        i++;
                    }
                }
                if (!monumentsVendables.empty()){
                    Controleur::getControleur()->afficher("Choisisez le monument a detruire pour gagner 8 pieces \n");
                    int reponse = std::stoi(Controleur::getControleur()->lire_str());
                    monumentsVendables[reponse]->detruire();
                    gain = 8;
                }
                else {
                    Controleur::getControleur()->afficher("Vous n'avez aucun monument a vendre \n");
                    gain = 0;
                } }
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

                Controleur::getControleur()->afficher("Choisisez un AUTRE joueur a qui gracieusement donner cette carte \n");
                //On peut choisir tous les joueurs sauf le joueur actif

                Joueur* joueurChoisi = Controleur::getControleur()->selection_joueur(jeu.getJoueursSansActifPtr());

                joueurChoisi->ajouterBatiment(batimentChoisi);
                joueurProprietaire->enleverBatiment(batimentChoisi);
                gain = 4;
            break;

        }

    }
    joueurActif->gagnerPieces(gain);
}


std::string CarteVerte::to_string() const {
    std::string res = "[" + this->getNom() + "] : produit <" + std::to_string(this->getGain()) + "> pièces sur (" ;
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
