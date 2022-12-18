#include "../headers/marche.h"
#include <algorithm> // pour le shuffle
#include <random>    // pour le shuffle

Batiment* Marche::piocherUneCarte() {
// Renvoie un pointeur sur la carte du dessus de la pioche, 
// et supprime le pointeur en question de la pioche.
    if (pioche.size() == 0) throw "Impossible de piocher une carte : la pioche est vide.";
    Batiment* c = pioche.back();
    pioche.pop_back();
    return c;
};

// méthode indiquant si une string str est présente dans un vecteur de strings v
bool isInVector(vector<string> v, string str){
    for(const string& s : v)
        if(s==str)
            return true;
    return false;
}

vector<Batiment*> Marche::getCarteDispAchat() const {
// Renvoie un vecteur d’exactement 9 éléments qui sont les 9 bâtiments 
// disponibles à l’achat (on ne prend donc pas en compte la multiplicité) :
    vector<string> nomsCartes;
    vector<Batiment*> ptCartes;
    for (Batiment* c : enJeu) {
        if (!isInVector(nomsCartes,c->getNom())){
            nomsCartes.push_back(c->getNom());
            ptCartes.push_back(c);
        }
    }
    return ptCartes;
};

int Marche::getTailleMarche() const {
// Renvoie le nombre de cartes *différentes* dans le vecteur enJeu.
    vector<Batiment*> res = getCarteDispAchat();
    return res.size();
};

void Marche::distribuer(){
// Exécute la méthode piocheUneCarte(), et ajoute les cartes au marché,
// jusqu’à ce que getTailleMarche() soit égal à 9.
    while(getTailleMarche() < 9 && pioche.size()!=0){
        enJeu.push_back(piocherUneCarte());
    }
};

void Marche::retirerCarteAchetee(Batiment* c){
// Supprime la carte achetée (par le joueur actif) du vecteur enJeu.
    for (auto it = enJeu.begin(); it != enJeu.end(); ++it){
        if(*it == c){
            enJeu.erase(it);
            break;
        }
    }
};

Batiment* Marche::acheter(int achat){
// Renvoie un pointeur sur la carte que le joueur actif a décidé d’acheter,
// et appelle les méthodes retirerCarteAchetee() puis distribuer().
// L’argument int permet de savoir lequel des 9 bâtiments du vecteur getCarteDispAchat() choisir.
    vector<Batiment*> liste = getCarteDispAchat();
    Batiment* c = liste[achat];
    retirerCarteAchetee(c);
    distribuer();
    return c;
};

void Marche::acheter(Batiment* b){
    retirerCarteAchetee(b);
    distribuer();
}

template<typename T>
void shuffle(vector<T> &vec){
    random_device rd;
    mt19937 g(rd());
    shuffle(vec.begin(), vec.end(), g);
}

Marche::Marche(vector<Batiment*> cartes):pioche(cartes) {
// Constructeur de la classe Marché.  Initialise la pioche à partir d’un vecteur de cartes,
// et appelle la méthode distribuer() pour répartir les cartes dans le vecteur enJeu.
    shuffle(pioche);
    distribuer();
};
