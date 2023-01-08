#include "../../metier/headers/cartesviolettes.h"
#include "../../metier/headers/enums.h"
#include "../../metier/headers/Jeu.h"
#include "../../metier/headers/Controleur.h"
#include <cmath>
#include "../../metier/headers/IA_drunken.h"

CarteViolette::CarteViolette(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, std::string description)
    : Batiment(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}
void CarteViolette::activer(Joueur *joueurProprietaire)
{
    string name = this->getNom();
    Controleur *controleur = Controleur::getControleur();

    controleur->afficher("Vous avez activé la carte " + name + "\n");
}

std::string CarteViolette::to_string() const
{
    std::string res = "[" + this->getNom() + "] " + std::to_string(this->getPrix()) + " : produit <" + std::to_string(this->getGain()) + "> pièces sur (";
    for (const auto &i : this->getCombinaisons())
    {
        res += std::to_string(i);
        res += ", ";
    }
    res += ") aux dés, ";

    switch (getId())
    {
    case 13: // stade
        res += "Insérer effet";
        break;

    case 14: // chaineTV
        res += "Insérer effet";
        break;

    case 15: // centreAffaires
        res += "Insérer effet";
        break;
    }
    return res;
}

CentreAffaires::CentreAffaires(int id, std::string nom, TypeBatiment type,
                               int prix, int gain, std::vector<int> combinaisons,
                               Couleur couleur, std::string description) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur, description)
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

CentreImpot::CentreImpot(int id, std::string nom, TypeBatiment type,
                         int prix, int gain, std::vector<int> combinaisons,
                         Couleur couleur, std::string description) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void CentreImpot::activer(Joueur *joueurProprietaire)
{
    CarteViolette::activer(joueurProprietaire); // affichage de l'activation de la carte

    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();

    for (auto &j : Jeu::getJeu().getJoueurs())
    {
        if (j->getPieces() >= 10)
            joueurActif->gagnerPieces(j->perdrePieces(floor(j->getPieces() / 2)));
    }
}

ChaineTV::ChaineTV(int id, std::string nom, TypeBatiment type,
                   int prix, int gain, std::vector<int> combinaisons,
                   Couleur couleur, std::string description) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void ChaineTV::activer(Joueur *joueurProprietaire)
{
    CarteViolette::activer(joueurProprietaire); // affichage de l'activation de la carte

    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur *controleur = Controleur::getControleur();

    controleur->afficher("A qui voulez vous prendre 5 pieces ? \n");

    Joueur *joueurChoisi = nullptr;

    if(joueurActif->isIA()){
        joueurChoisi = static_cast<IA_drunken*>(joueurChoisi)->choixJoueur(Jeu::getJeu().getJoueursSansActifPtr());
    }else{
        joueurChoisi = controleur->selection_joueur(Jeu::getJeu().getJoueursSansActifPtr());
    }

    int vol = joueurChoisi->perdrePieces(5);
    joueurActif->gagnerPieces(vol);
}

MaisonEdition::MaisonEdition(int id, std::string nom, TypeBatiment type,
                             int prix, int gain, std::vector<int> combinaisons,
                             Couleur couleur, std::string description) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void MaisonEdition::activer(Joueur *joueurProprietaire)
{
    CarteViolette::activer(joueurProprietaire); // affichage de l'activation de la carte

    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur *controleur = Controleur::getControleur();

    int compteur = 0;
    for (auto &j : Jeu::getJeu().getJoueurs())
    {
        compteur = 0;
        for (auto &b : j->getConstructions())
            if (b->getType() == TypeBatiment::magasin || b->getType() == TypeBatiment::restaurant)
                compteur += 1;
        joueurActif->gagnerPieces(j->perdrePieces(compteur));
    }
}

Stade::Stade(int id, std::string nom, TypeBatiment type,
             int prix, int gain, std::vector<int> combinaisons,
             Couleur couleur, std::string description) : CarteViolette(id, nom, type, prix, gain, combinaisons, couleur, description)
{
}

void Stade::activer(Joueur *joueurProprietaire)
{
    CarteViolette::activer(joueurProprietaire); // affichage de l'activation de la carte

    Joueur *joueurActif = Jeu::getJeu().getJoueurActif();
    Controleur *controleur = Controleur::getControleur();

    for (auto &j : Jeu::getJeu().getJoueurs())
    {
        if (j != joueurActif)
        {
            joueurActif->gagnerPieces(j->perdrePieces(2));
        }
    }
}
