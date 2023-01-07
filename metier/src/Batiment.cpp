#include "../headers/Batiment.h"
#include "../headers/Jeu.h"

Batiment::Batiment(int id, std::string nom, TypeBatiment t, int prix, int gain, std::vector<int> combinaisons, Couleur c)
    : Carte(id, nom, prix), combinaisons(combinaisons), type(t), gain(gain), couleur(c) {

}

Batiment::~Batiment(){};

void Batiment::acheter(){
    Jeu::getJeu().getJoueurActif()->ajouterBatiment(this);
    Jeu::getJeu().getMarche()->acheter(this);
};

QString Batiment::getStyle(){
    QString res;
    switch(this->couleur) {
    case Couleur::Bleu :
        res = "rgb(20,80,230)";
    break;


    case Couleur::Rouge :
        res = "rgb(240,60,0)";
    break;


    case Couleur::Vert :
        res = "rgb(40,220,0)";
    break;


    case Couleur::Violet :
        res = "rgb(200,0,230)";
    break;
    }
    return res;
}
