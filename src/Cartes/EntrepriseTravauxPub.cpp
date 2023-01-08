#include "../../headers/Cartes/EntrepriseTravauxPub.h"
#include <vector>
#include "headers/Joueur.h"
#include "headers/Monument.h"
#include "headers/Controleur.h"

EntrepriseTravauxPub::EntrepriseTravauxPub(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur)
    : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur)
{
}

void EntrepriseTravauxPub::activer(Joueur *joueurProprietaire)
{
    std::vector<Monument *> monumentsVendables;
    Controleur::getControleur()->afficher("Liste des monuments construits : \n");
    for (auto &monu : joueurProprietaire->getMonuments())
    {
        if (monu->getConstruit())
        {
            monumentsVendables.push_back(monu);
        }
    }

    if (!monumentsVendables.empty())
    {
        Controleur::getControleur()->afficher("Choisisez le monument à detruire pour gagner 8 pièces \n");
        Monument *reponse = Controleur::getControleur()->selection_monument(monumentsVendables);
        reponse->detruire();
        this->setGain(8);
    }
    else
    {
        Controleur::getControleur()->afficher("Vous n'avez aucun monument à vendre \n");
        this->setGain(0);
    }
    CarteVerte::activer(joueurProprietaire);
}
