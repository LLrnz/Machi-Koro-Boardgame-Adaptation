#include "../../headers/Cartes/MonsterSoda.h"
#include "headers/Jeu.h"

MonsterSoda::MonsterSoda(int id, std::string nom, TypeBatiment type, int prix, int gain, std::vector<int> combinaisons, Couleur couleur, TypeBatiment effectType)
    : CarteVerte(id, nom, type, prix, gain, combinaisons, couleur), effectType(effectType)
{
}

void MonsterSoda::activer(Joueur *joueurProprietaire)
{
    int compteur = 0;
    for (auto &i : Jeu::getJeu().getJoueurs())
    { // pour chaque joueur
        for (auto &j : i.getConstructions())
        {                                        // pour chaque batiment du joueur
            if (j->getType() == this->getEffectType()) // si le batiment est du type de l'effet
                compteur++;
        }
    }
    this->setGain(compteur);
    CarteVerte::activer(joueurProprietaire);
}
