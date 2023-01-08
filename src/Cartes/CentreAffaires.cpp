#include "../../headers/Cartes/CentreAffaires.h"
#include "../../headers/Jeu.h"
#include "../../headers/Controleur.h"

CentreAffaires::CentreAffaires(int id, std::string nom, TypeBatiment type,
                               int prix, int gain, std::vector<int> combinaisons,
                               Couleur couleur) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void CentreAffaires::activer(Joueur *joueurProprietaire)
{
    CarteViolette::activer(joueurProprietaire); // affichage de l'activation de la carte

    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur *controleur = Controleur::getControleur();

    // Affichage et selection de la personne avec qui échange run batiment
    controleur->afficher("Avec qui voulez vous echanger un etablissement ? \n");
    controleur->afficher("-1 : Personne \n");
    Joueur *joueurVise = controleur->selection_joueur_batiment(Jeu::getJeu().getJoueursSansActifPtr());

    // Si il choisis -1, il n'effectue pas d'échange
    // Séquence d'échange
    if (joueurVise != nullptr)
    {
        // Affichage et selection de la carte a prendre chez l'adversaire (ou vous même)
        controleur->afficher("Choisisez la carte a prendre depuis chez ");
        controleur->afficher(joueurVise->getPseudo());
        controleur->afficher("\n");

        Batiment *repPrendre = controleur->selection_batiment(joueurVise->getConstructions());

        controleur->afficher("Choisisez la carte a echanger depuis chez vous");
        controleur->afficher(joueurActif->getPseudo());
        controleur->afficher("\n");

        Batiment *repEchange = controleur->selection_batiment(joueurActif->getConstructions());

        joueurActif->ajouterBatiment(repPrendre);
        joueurVise->ajouterBatiment(repEchange);
        joueurActif->enleverBatiment(repEchange);
        joueurVise->enleverBatiment(repPrendre);
    }
    else
    {
        controleur->afficher("Echange annulé./n");
    }
}