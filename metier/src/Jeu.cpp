#include "../headers/Controleur.h"

#include "../headers/services.h"
#include <QtCore>
#include <iostream>
#include <cstdlib>
#include <sstream>

// pour le lancé de dés
#include <random>
#include <algorithm>


using namespace std;

/**
 * Constructeur de jeu
 * @brief Jeu::Jeu
 */
Jeu::Jeu():cartesEnJeu(), joueurs(), joueurActif(nullptr), marche(nullptr){

}
void Jeu::initialiserCartes(map<Extensions, bool> extensions) {// charger le fichier json
    cartesEnJeu = Service::chargerFichier(extensions);

}

/**
 * Destructeur de jeu
 * @brief Jeu::~Jeu
 */
Jeu::~Jeu() {
    delete marche;
    for (Batiment* c : cartesEnJeu) {
        delete c;
    }
}

/**
 * Fonction de test seulement, à ne pas utiliser !!
 * @brief Jeu::afficherCartes
 */
void Jeu::afficherCartes() {
    std::cout << "affichage des cartes en jeu :" << std::endl;
    for (Batiment* c : cartesEnJeu) {
        std::cout << c->getNom() << std::endl;
    }
    std::cout << "Il y a " << cartesEnJeu.size() << " cartes en jeu." << std::endl;
}

Jeu* Jeu::jeu = nullptr;

/**
 * @brief Jeu::getJeu
 * @return l'intance du singleton jeu
 */
Jeu& Jeu::getJeu() {
    if (Jeu::jeu == nullptr){
        Jeu::jeu = new Jeu;}
    return *jeu;
}

/**
 * libère le singleton
 * @brief Jeu::libererJeu
 */
void Jeu::libererJeu() {
	delete jeu;
	jeu = nullptr;
}

/**
 * @brief Jeu::initialiserJoueurs
 * @param listeJoueurs les pseudos et types des joueurs de la partie
 */
void Jeu::initialiserJoueurs(map<std::string, TypeJoueur> listeJoueurs) {
    for (const auto &j : listeJoueurs) {
        std::string pseudo = j.first;
        TypeJoueur type = j.second;
        joueurs.push_back(Joueur(pseudo, type));
	}
}


/**
 * @brief Jeu::genererPartie
 * @param listeJoueurs : les pseudos et types des joueurs de la partie
 * @param extensions : les extensions en jeu ou non
 */
void Jeu::genererPartie(map<std::string, TypeJoueur> listeJoueurs, map<Extensions, bool> extensions) {
    this->initialiserJoueurs(listeJoueurs);
    this->initialiserCartes(extensions);
    this->donnerCarteDeBase();

    //this->afficherCartes();
    marche = new Marche(cartesEnJeu);

    //initialisation condition Victoire en fonction du nombre d'extensions en jeu
    if(Controleur::getControleur()->getExtensions().size() > 1){
        this->conditionVictoire = 5;
    }else{
        this->conditionVictoire = 4;
    }

    this->joueurActif = joueurs.begin();
}

void Jeu::donnerCarteDeBase(){
    for(auto &j : this->joueurs){
        Batiment* boulangerie = nullptr;
        Batiment* champsdeble = nullptr;
        bool champTrouve = false;
        bool boulangeTrouve = false;

        for(auto b = cartesEnJeu.begin(); b != cartesEnJeu.end(); ++b){
            Batiment* tmp = *b;
            if(tmp->getCouleur() == Couleur::Bleu && tmp->getId() == 1 && !champTrouve){
                champsdeble = *b;
                cartesEnJeu.erase(b);
                champTrouve = true;
            }
            if(tmp->getCouleur() == Couleur::Vert && tmp->getId() == 1 && !boulangeTrouve){
                boulangerie = *b;
                cartesEnJeu.erase(b);
                boulangeTrouve = false;
            }
        }

        j.ajouterBatiment(boulangerie);
        j.ajouterBatiment(champsdeble);
    }
}


/**
 * @brief Jeu::boucleDeJeu
 */
void Jeu::boucleDeJeu() {


    //Tant que la parti n'es pas terminée, commencer une manche
	while (partieTerminee == false) {

        //Jouer le tour de chaque joueur
        for(auto &j : joueurs){
            //joueurActif= &j;
            //jeu->tourDeJeu();
        }

	}
	
    Controleur::getControleur()->afficher("Le joueur ");
    Controleur::getControleur()->afficher(joueurActif->getPseudo());
    Controleur::getControleur()->afficher("a gagné la partie ! \n");
}

/**
 * @brief Jeu::tourDeJeu exprime un tour de jeu
 */
bool Jeu::finDeTour() {

    partieTerminee = jeu->verifierVictoire();
    jeu->joueurSuivant();
    return partieTerminee;
}

void Jeu::joueurSuivant(){
    joueurActif++;
    if(joueurActif == joueurs.end()){
        joueurActif = joueurs.begin();
    }
}

void Jeu::activerCartes(int resultatJet){
    jeu->activerCartesRouges(resultatJet);
    jeu->activerCartesBleues(resultatJet);
    jeu->activerCartesVertes(resultatJet);
    jeu->activerCartesViolettes(resultatJet);
}

/**
 * @brief Jeu::verifierVictoire
 * @return vrai si un joueur a gagné, sinon faux
 */
bool Jeu::verifierVictoire(){
    bool res = false;

    if (joueurActif->getNbMonumentsConstruits()>=conditionVictoire)
            res = true;

    return res;
}

int aleat(int min, int max){
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> d(min, max);
    return d(g);
}

int Jeu::lancer1de(){
    int resultatJet;
    resultatJet = aleat(1,6);

    this->lancerDes(resultatJet);
    this->afficherDes(resultatJet);
    return resultatJet;
}

int Jeu::lancer2des(){
    int resultatJet;
    int de1 = aleat(1,6);
    int de2 = aleat(1,6);
    resultatJet = de1 + de2;

    if ((de1 == de2) && joueurActif->hasParcAttractions()){
        Controleur::getControleur()->afficher("Le resultat est un double, vous rejouez un tour après celui ci ! \n");
        joueurActif->setRejoueTour(true);
    }
    else
        joueurActif->setRejoueTour(false);


    this->lancerDes(resultatJet);
    this->afficherDes(resultatJet);
    return resultatJet;
}

/**
 * @brief Execute le jet de dés en fonctions des modificateurs de lancés que le joueur possède
 * @return le nombre aux lancé de dés du joueur
 */
void Jeu::afficherDes(int resultatJet){
    Controleur::getControleur()->afficher("Le résultat du jet est ");
    Controleur::getControleur()->afficher(to_string(resultatJet));
    Controleur::getControleur()->afficher("\n");
}

/**
 * @brief Encapsule le jet de dé pour permettre aux possesseurs d'une tour radio de le relancer
 * @return Le numéro aux dés
 */
void Jeu::lancerDes(int resultatJet){

}

/**
 * @brief Phase d'achat où le joueur peut acheter une carte
 */
bool Jeu::achat(Carte* c){
// 6e étape de la boucle de jeu. Propose au joueur la liste des cartes achetables
// du Marché, puis appelle la méthode acheter() du Marché.
    
    int soldeJoueur = joueurActif->getPieces();
    bool res;

    Controleur::getControleur()->afficher("\nVous avez choisi : " + c->getNom() + ".\n");
    if(soldeJoueur >= c->getPrix()){
        c->acheter();
        joueurActif->perdrePieces(c->getPrix());
        res = true;
    }else{
        res = false;
    }

    return res;
};

void Jeu::toucherRSA(){
    if (joueurActif->getPieces() < 2)
        joueurActif->gagnerPieces(2-joueurActif->getPieces());

    if(joueurActif->hasAeroport())
    joueurActif->gagnerPieces(10);
}


void Jeu::activerCartesRouges(int nbDes){
    for (auto &j : joueurs)
        if(&j != joueurActif.base()) //Peut etre que ça marhce pas
            j.activerCartesRouges(nbDes);
}
void Jeu::activerCartesBleues(int nbDes){
    for (auto &j : joueurs)
        j.activerCartesBleues(nbDes);
}

void Jeu::activerCartesVertes(int nbDes){
    joueurActif->activerCartesVertes(nbDes);
}
void Jeu::activerCartesViolettes(int nbDes){
    joueurActif->activerCartesViolettes(nbDes);
}

int Jeu::getNbJoueurs() const{
    return joueurs.size();
}

vector<Joueur*> Jeu::getJoueursSansActifPtr(){
    vector<Joueur*> res;
    for(auto &j : joueurs){
        if(&j != joueurActif.base())
        res.push_back(&j);
    }
    return res;
}

void Jeu::setDesRelances(bool val){
    this->deRelances = val;
}


