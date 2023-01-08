#include "../headers/Batiment.h"
#include "../headers/Jeu.h"

Batiment::Batiment(int id, std::string nom, TypeBatiment t, int prix, int gain, std::vector<int> combinaisons, Couleur c, std::string description)
    : Carte(id, nom, prix), combinaisons(combinaisons), type(t), gain(gain), couleur(c), description(description) {

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
        res = "rgb(130, 228, 244)";
    break;


    case Couleur::Rouge :
        res = "rgb(255, 159, 159)";
    break;


    case Couleur::Vert :
        res = "rgb(190, 247, 159)";
    break;


    case Couleur::Violet :
        res = "rgb(228, 159, 255)";
    break;
    }
    return res;
}
