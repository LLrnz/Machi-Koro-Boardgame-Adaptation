#include "../headers/marche.h"
#include <algorithm> // pour le shuffle
#include <random>    // pour le shuffle

/*!
 * \brief Pioche une carte
 * \return le pointeur sur la carte piochée
 */
Batiment* Marche::piocherUneCarte() {
// Renvoie un pointeur sur la carte du dessus de la pioche, 
// et supprime le pointeur en question de la pioche.
    if (pioche.size() == 0) throw "Impossible de piocher une carte : la pioche est vide.";
    Batiment* c = pioche.back();
    pioche.pop_back();
    return c;
};

//
/*!
 * \brief méthode indiquant si une string str est présente dans un vecteur de strings v
 * \param v
 * \param str
 * \return
 */
bool isInVector(vector<string> v, string str){
    for(const string& s : v)
        if(s==str)
            return true;
    return false;
}

/*!
 * \brief Marche::getCarteDispAchat
 * \return la liste des cartes achetables
 */
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

/*!
 * \brief Marche::getTailleMarche
 * \return le nombre de cartes du marché
 */
int Marche::getTailleMarche() const {
// Renvoie le nombre de cartes *différentes* dans le vecteur enJeu.
    vector<Batiment*> res = getCarteDispAchat();
    return res.size();
};

/*!
 * \brief pioche jusqu'à ce qu'il y ait 9 cartes différentes
 */
void Marche::distribuer(){
// Exécute la méthode piocheUneCarte(), et ajoute les cartes au marché,
// jusqu’à ce que getTailleMarche() soit égal à 9.
    while(getTailleMarche() < 9 && pioche.size()!=0){
        enJeu.push_back(piocherUneCarte());
    }
};

/*!
 * \brief Marche::retirerCarteAchetee
 * \param c : pointeur sur la carte à retirer
 */
void Marche::retirerCarteAchetee(Batiment* c){
// Supprime la carte achetée (par le joueur actif) du vecteur enJeu.
    for (auto it = enJeu.begin(); it != enJeu.end(); ++it){
        if(*it == c){
            enJeu.erase(it);
            break;
        }
    }
};

//Batiment* Marche::acheter(int achat){
//// Renvoie un pointeur sur la carte que le joueur actif a décidé d’acheter,
//// et appelle les méthodes retirerCarteAchetee() puis distribuer().
//// L’argument int permet de savoir lequel des 9 bâtiments du vecteur getCarteDispAchat() choisir.
//    vector<Batiment*> liste = getCarteDispAchat();
//    Batiment* c = liste[achat];
//    retirerCarteAchetee(c);
//    distribuer();
//    return c;
//};

/*!
 * \brief acheter une carte : retirer une carte puis reremplir le marcher
 * \param b : pointeur sur carte à acheter
 */
void Marche::acheter(Batiment* b){
    retirerCarteAchetee(b);
    distribuer();
}

template<typename T>
/*!
 * \brief shuffle mélange la pioche
 * \param vec
 */
void shuffle(vector<T> &vec){
    random_device rd;
    mt19937 g(rd());
    shuffle(vec.begin(), vec.end(), g);
}

/*!
 * \brief constructeur du marcher
 * \param cartes en jeu
 */
Marche::Marche(vector<Batiment*> cartes):pioche(cartes) {
// Constructeur de la classe Marché.  Initialise la pioche à partir d’un vecteur de cartes,
// et appelle la méthode distribuer() pour répartir les cartes dans le vecteur enJeu.
    shuffle(pioche);
    distribuer();
};
