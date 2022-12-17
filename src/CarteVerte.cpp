#include "./../headers/CarteVerte.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include <sstream>

CarteVerte::CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur), effectType(effectType){}


void CarteVerte::activer(Joueur joueurProprietaire){
    Joueur joueurActif = Jeu::getJeu()->getJoueurActif();
    vector<Joueur> joueurs = Jeu::getJeu()->getJoueurs();
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
            for (auto i = Jeu::getJeu()->getJoueurs().begin(); i != Jeu::getJeu()->getJoueurs().end(); i++){          // pour chaque joueur
                for (auto j = (*i).getConstructions().begin(); j != (*i).getConstructions().end(); j++){                // pour chaque batiment du joueur
                    if ((*j)->getType() == getEffectType())                                                                 // si le batiment est du type de l'effet
                        compteur++;
                }
            }
            gain = compteur;
        }
        else {                                                                                             // si ce n'est pas Moonster soda
            for (auto it = joueurActif.getConstructions().begin(); it != joueurActif.getConstructions().end(); it++){ // pour chaque batiment du joueur actif
                if ((*it)->getType() == getEffectType()){                                                              // si le batiment est du type de l'effet
                    compteur ++;
                }
                gain = this->getGain() * compteur;
            }
        }
    }
    else if (idCarte == 8){                                                                                // si c'est Epicerie
        for (int i = 0; i < size(joueurActif.getMonuments()); i++){                                             // pour chaque monument du joueur actif
            if (joueurActif.getMonuments()[i].getConstruit() == true){                                              // si le monument est construit
                compteur += 1;
            }
        }
        if (compteur >= 2){                                                                               // si le joueur a construit au moins 2 monuments
            gain = 0;                                                                                           // il ne gagne rien
        }
    }
    else if (idCarte == 6){                                                                                 // si c'est Fleuriste
        for (auto it = joueurActif.getConstructions().begin(); it != joueurActif.getConstructions().end(); it++){   // pour chaque batiment du joueur actif
            if ((*it)->getId() == 9)                                                            // si le batiment est un champ de fleurs (voir CarteBleue.cpp)
                compteur += 1;
            gain = compteur;
        }
    }
    // ! Revoir cette partie
    else if (idCarte == 9){  // si c'est Entreprise de travaux publics
        vector<Monument*> monumentsVendables; 
        int i = 0;
        stringstream s;
        Controleur::getControleur()->afficher("Liste des monuments construits : \n");
        for (Monument monu : joueurProprietaire.getMonuments()){
            if (monu.getConstruit()){
                monumentsVendables.push_back(&monu);
                s.str("");
                s << "  " << i << " : " << monu.getNom() << ")\n";
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
        } 
    }
    // ! Finir ça
    else if (idCarte == 11){                                                                        // si c'est Entreprise de déménagement
        stringstream s;
        Controleur::getControleur()->afficher("Liste des cartes possibles à déménager : \n");     // on affiche les cartes possibles à déménager
        for (size_t i = 0; i<joueurProprietaire.getConstructions().size();i++){  // pour chaque batiment du joueur actif
            if (joueurProprietaire.getConstructions()[i]->getType()!=TypeBatiment::special)
                s << i << " : " << joueurProprietaire.getConstructions()[i]->getNom() << "\n";
        }
        Controleur::getControleur()->afficher("Votre choix : \n");
        int choixIndiceBatiment = std::stoi(Controleur::getControleur()->lire_str());
        Controleur::getControleur()->afficher("Choisisez un AUTRE joueur a qui gracieusement donner cette carte \n");
        for (size_t i =0; i< joueurs.size();i++){
            if (Jeu::getJeu()->getIndiceJoueurActif()!=i){
                s.str("");
                s << i << " : " << joueurs[i].getPseudo() << "\n";
                Controleur::getControleur()->afficher(s.str());
            }
        }
        int joueurChoisi = std::stoi(Controleur::getControleur()->lire_str());
        if (joueurChoisi == Jeu::getJeu()->getIndiceJoueurActif()){
            gain = 0;
            Controleur::getControleur()->afficher("Apprend a lire les instructons");
        }
        else {
            Batiment* batimentDonne = joueurProprietaire.getConstructions()[choixIndiceBatiment];
            joueurs[joueurChoisi].ajouterBatiment(batimentDonne);
            joueurProprietaire.enleverBatimentParIndice(choixIndiceBatiment);
            gain = 4;
        }
    }

    // affichage
    Controleur::getControleur()->afficher(s.str());
    joueurActif.gagnerPieces(gain);
}
