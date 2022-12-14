#include "../headers/Marche.h"

Carte* Marche::piocherUneCarte() {
// Renvoie un pointeur sur la carte du dessus de la pioche, 
// et supprime le pointeur en question de la pioche.
    if (pioche.size() == 0) throw "Impossible de piocher une carte : la pioche est vide.";
    Carte* c = pioche.back();
    pioche.pop_back();
    return c;
};


vector<Carte*> Marche::getCarteDispAchat() const {
// Renvoie un vecteur d’exactement 9 éléments qui sont les 9 bâtiments 
// disponibles à l’achat (on ne prend donc pas en compte la multiplicité) :
    vector<string> nomsCartes;
    vector<Carte*> ptCartes;
    for (Carte* c : enJeu) {
        string nom = c->getNom();
        bool CarteDejaDansLaListe = (find(nomsCartes.begin(), nomsCartes.end(), nom) != nomsCartes.end());
        if (!CarteDejaDansLaListe){
            nomsCartes.push_back(nom);
            ptCartes.push_back(c);
        }
    }
    return ptCartes;
};


int Marche::getTailleMarche() const {
// Renvoie le nombre de cartes *différentes* dans le vecteur enJeu.
    vector<Carte*> res = getCarteDispAchat();
    return res.size();
};

void Marche::distribuer(){
// Exécute la méthode piocheUneCarte(), et ajoute les cartes au marché,
// jusqu’à ce que getTailleMarche() soit égal à 9.
    while(getTailleMarche() < 9 && pioche.size()!=0){
        enJeu.push_back(piocherUneCarte());
    }
};

void Marche::retirerCarteAchetee(Carte* c){
// Supprime la carte achetée (par le joueur actif) du vecteur enJeu.
    for (auto it = enJeu.begin(); it != enJeu.end(); ++it){
        if(*it == c){
            enJeu.erase(it);
            break;
        }
    }
};

Carte* Marche::acheter(int achat){
// Renvoie un pointeur sur la carte que le joueur actif a décidé d’acheter,
// et appelle les méthodes retirerCarteAchetee() puis distribuer().
// L’argument int permet de savoir lequel des 9 bâtiments du vecteur getCarteDispAchat() choisir.
    vector<Carte*> liste = getCarteDispAchat();
    Carte* c = liste[achat];
    retirerCarteAchetee(c);
    distribuer();
    return c;
};


Marche::Marche(vector<Carte*> cartes):pioche(cartes) {
// Constructeur de la classe Marché.  Initialise la pioche à partir d’un vecteur de cartes,
// et appelle la méthode distribuer() pour répartir les cartes dans le vecteur enJeu.
    distribuer();
};