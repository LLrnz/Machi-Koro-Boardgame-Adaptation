#include "./../headers/CarteVerte.h"
#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include <sstream>

CarteVerte::CarteVerte(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur), effectType(effectType)
{
}

TypeBatiment CarteVerte::getEffectType()
{
    return effectType;
}

void CarteVerte::activer(Joueur joueurProprietaire){
    Joueur joueurActif = Jeu::getJeu().getJoueurActif();
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
            for (auto i = Jeu::getJeu().getJoueurs().begin(); i != Jeu::getJeu().getJoueurs().end(); i++){          // pour chaque joueur
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
    else if (idCarte == 9){                                                                            // si c'est Entreprise de travaux publics
        std::vector<string> monumentsConstruits;                                              // vecteur qui contient les noms des monuments construits
        for (auto i = joueurActif.getMonuments().begin(); i != joueurActif.getMonuments().end(); i++)       // pour chaque monument du joueur actif
            if ((*i).getConstruit() == true)                                                         // si le monument est construit
                monumentsConstruits.push_back((*i).getNom());                                  // on ajoute son nom au vecteur

        if (!monumentsConstruits.empty())                                                          // si le vecteur n'est pas vide{
            Controleur::getControleur()->afficher("Vous devez retourner une de vos cartes monuments sur sa face travaux : \n"); // on affiche les monuments construits
            stringstream s;
            for (auto i = monumentsConstruits.begin(); i != monumentsConstruits.end(); i++){        // pour chaque monument construit
                s << "-" << *i << ")\n";
                Controleur::getControleur()->afficher(s.str());                                     // on affiche le nom du monument
            }
            Controleur::getControleur()->afficher("Quel batiment voulez vous mettre en travaux : ");    // on demande à l'utilisateur de choisir un monument

            // ! revoir pour utiliser les id plutôt que les noms
            string choix = Controleur::getControleur()->lire();

            for (auto i = joueurActif.getMonuments().begin(); i != joueurActif.getMonuments().end(); i++){
                if ((*i).getNom() == choix) {
                    (*i).detruit();
                }
            }
        }

    // ! Finir ça
    else if (idCarte == 11){                                                                        // si c'est Entreprise de déménagement
        stringstream s;
        int n = 0;
        Controleur::getControleur()->afficher("Liste des cartes possibles à déménager : \n");     // on affiche les cartes possibles à déménager
        for (auto i = joueurActif.getConstructions().begin(); i != joueurActif.getConstructions().end(); i++)   // pour chaque batiment du joueur actif
        {
            if ((*i)->getType() != TypeBatiment::special)                                         // si le batiment n'est pas spécial
            {
                s << "-" << (*i)->getNom() << " (" << n++ << ")\n";
                Controleur::getControleur()->afficher(s.str());
            }
        }
        Controleur::getControleur()->afficher("Votre choix : ");
        int choix = std::stoi(Controleur::getControleur()->lire());
        bool demenagement = false;
        n = 0;
        for (auto i = joueurActif.getConstructions().begin(); demenagement && i != joueurActif.getConstructions().end(); i++)   // pour chaque batiment du joueur actif
        {
            if ((*i)->getType() != TypeBatiment::special){                                       // si le batiment n'est pas spécial
                if (n++ == choix){
                    // Echange avec le joueur à choisir
                    Controleur::getControleur()->afficher("Chez qui voulez vous déménager : \n");
                    for (auto j = Jeu::getJeu().getJoueurs().begin(); j != Jeu::getJeu().getJoueurs().end(); j++){

                    }
                    demenagement = true;
                }
            }
        }
    }

    // affichage
    Controleur::getControleur()->afficher(s.str());
    joueurActif.gagnerPieces(gain);
}
