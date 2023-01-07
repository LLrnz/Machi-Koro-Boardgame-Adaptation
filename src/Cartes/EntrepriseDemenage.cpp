#include "../../headers/Cartes/EntrepriseDemenage.h"
#include "../../headers/Controleur.h"
#include <vector>

EntrepriseDemenage::EntrepriseDemenage(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur) : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void EntrepriseDemenage::activer(Joueur *joueurProprietaire)
{
    Controleur::getControleur()->afficher("Liste des cartes possibles à déménager : \n"); // on affiche les cartes possibles à déménager
    vector<Batiment *> choixBatiments;
    for (auto &b : joueurProprietaire->getConstructions())
    { // pour chaque batiment du joueur actif
        if (b->getType() != TypeBatiment::special)
            choixBatiments.push_back(b);
    }

    Controleur::getControleur()->afficher("Votre choix : \n");
    Batiment *batimentChoisi = Controleur::getControleur()->selection_batiment(choixBatiments);

    Controleur::getControleur()->afficher("Choisisez un AUTRE joueur à qui gracieusement donner cette carte \n");
    // On peut choisir tous les joueurs sauf le joueur actif

    Joueur *joueurChoisi = Controleur::getControleur()->selection_joueur(Jeu::getJeu().getJoueursSansActifPtr());

    joueurChoisi->ajouterBatiment(batimentChoisi);
    joueurProprietaire->enleverBatiment(batimentChoisi);
    this->setGain(4);
}