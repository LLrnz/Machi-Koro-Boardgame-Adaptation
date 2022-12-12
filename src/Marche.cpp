#include "../headers/Marche.h"

Carte& Marche::piocherUneCarte() {
// Renvoie une référence sur la carte du dessus de la pioche, 
// et supprime ladite référence de la pioche.
    if (pioche.size()==0) throw "Impossible de piocher une carte : la pioche est vide.";
    Carte c = pioche.back();
    pioche.pop_back();
    return c;
};

int Marche::getTailleMarche() const {
// Renvoie le nombre de cartes *différentes* dans le vecteur enJeu.
// méthode : on fait une liste sans doublon des noms des cartes en jeu, et on compte.
    vector<string> nomsCartes;
    for (Carte c : enJeu){
        string nom = c.getNom();
        bool CarteDejaDansLaListe = (find(enJeu.begin(), enJeu.end(), nom) != enJeu.end());
        if(!CarteDejaDansLaListe) 
            nomsCartes.push_back(nom);
    }
    return nomsCartes.size();
};

void Marche::distribuer(){
// Exécute la méthode piocheUneCarte(), et ajoute les cartes au marché,
// jusqu’à ce que getTailleMarche() soit égal à 9.
    while(getTailleMarche() < 9 && pioche.size()!=0){
        enJeu.push_back(piocherUneCarte());
    }
};

void Marche::retirerCarteAchetee(Carte& c){
// Supprime la carte achetée (par le joueur actif) du vecteur enJeu.
    for (auto it = enJeu.begin(); it != enJeu.end(); ++it){
        if((*it).getId() == c.getId()){
            enJeu.erase(it);
        }
    }
};