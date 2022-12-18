#include "../headers/Controleur.h"

#include "services.cpp"
#include <QtCore>
#include <iostream>
#include <cstdlib>
#include <sstream>

// pour le lancé de dés
#include <random>
#include <algorithm>

// pour mettre des couleurs simplement dans le terminal (ANSI escape strings)
#define NC "\e[0m" // no color
#define RED "\e[0;91m" // light red
#define GRN "\e[0;92m" // light green
#define YLW "\e[0;93m" // light yellow
#define CYN "\e[0;96m" // light cyan

using namespace std;

/**
 * Constructeur de jeu
 * @brief Jeu::Jeu
 */
Jeu::Jeu():cartesEnJeu(), joueurs(), joueurActif(nullptr), marche(nullptr){

}
void Jeu::initialiserCartes(map<Extensions, bool> extensions) {// charger le fichier json
    cartesEnJeu = chargerFichier(extensions);
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
    //this->afficherCartes();
    marche = new Marche(cartesEnJeu);

    //initialisation condition Victoire en fonction du nombre d'extensions en jeu
    for (const auto &e : Controleur::getControleur()->getExtensions())
        if (e.second)
            this->conditionVictoire = 5;
        else
            this->conditionVictoire = 4;
}


/**
 * @brief Jeu::boucleDeJeu
 */
void Jeu::boucleDeJeu() {


    //Tant que la parti n'es pas terminée, commencer une manche
	while (partieTerminee == false) {

        //Jouer le tour de chaque joueur
        for(auto &j : joueurs){
            joueurActif = &j;
            jeu->tourDeJeu();
        }

	}
	
    Controleur::getControleur()->afficher("Le joueur ");
    Controleur::getControleur()->afficher(joueurActif->getPseudo());
    Controleur::getControleur()->afficher("a gagne la partie ! \n");
}

/**
 * @brief Jeu::tourDeJeu exprime un tour de jeu
 */
void Jeu::tourDeJeu() {
    Controleur::getControleur()->afficher(CYN "\nC'est à " + joueurActif->getPseudo() + " de jouer !\n" NC);
    Controleur::getControleur()->afficher("Vous possédez actuellement les cartes suivantes : \n");
    Controleur::getControleur()->afficher(joueurActif->getConstructions());

	int resultatJet = jeu->lancerDes();
	jeu->activerCartesRouges(resultatJet);
	jeu->activerCartesBleues(resultatJet);
	jeu->activerCartesVertes(resultatJet);
	jeu->activerCartesViolettes(resultatJet);
    Controleur::getControleur()->afficher(YLW "Vous avez " + to_string(joueurActif->getPieces()) + " pièces. \n" NC);
    jeu->achat();
    partieTerminee = jeu->verifierVictoire();
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

/**
 * @brief Execute le jet de dés en fonctions des modificateurs de lancés que le joueur possède
 * @return le nombre aux lancé de dés du joueur
 */
int Jeu::jetDes(){
	int resultatJet;
    if (joueurActif->hasGare() == true){
        Controleur::getControleur()->afficher("1 : Lancer un de \n");
        Controleur::getControleur()->afficher("2 : Lancer deux des \n");
        int reponse = Controleur::getControleur()->lire_int(1,2);

        //le joueur lance 2 dés
        if (reponse == 2){
            int de1 = aleat(1,6);
            int de2 = aleat(1,6);
			resultatJet = de1 + de2;

            if ((de1 == de2) && joueurActif->hasParcAttractions()){
                Controleur::getControleur()->afficher("Le resultat est un double, vous rejouez un tour apres celui ci ! \n");
                joueurActif->setRejoueTour(true);
			}
			else
                joueurActif->setRejoueTour(false);
		}
        //le joueur lance 1 dé
		else
            resultatJet = aleat(1,6);
	}
    //le joueur n'a pas le choix de lancer 1 dé
	else
        resultatJet = aleat(1,6);

    //Avec le port, le joueur peut moduler son jet
    if ((resultatJet >= 10) && (joueurActif->hasPort())){
        Controleur::getControleur()->afficher("Le resultat est superieur a 10 ! \n");
        Controleur::getControleur()->afficher("Le resultat du jet est ");
        Controleur::getControleur()->afficher(to_string(resultatJet));
        Controleur::getControleur()->afficher("Vous pouvez ajouter de 0 à 2 à votre jet. Combien ajouter ? \n");
        int rep = Controleur::getControleur()->lire_int(0, 2);
        resultatJet += rep;
	}


    Controleur::getControleur()->afficher("Le resultat du jet est ");
    Controleur::getControleur()->afficher(to_string(resultatJet));
    Controleur::getControleur()->afficher("\n");
	return resultatJet;
}

/**
 * @brief Encapsule le jet de dé pour permettre aux possesseurs d'une tour radio de le relancer
 * @return Le numéro aux dés
 */
int Jeu::lancerDes(){
	int resultatJet = jetDes();
    if (joueurActif->hasTourRadio()){
        Controleur::getControleur()->afficher("0 : Ne pas relancer les des \n");
        Controleur::getControleur()->afficher("1 : Relancer les des \n");
        int reponse = Controleur::getControleur()->lire_int(0, 1);
        if (reponse)
			resultatJet = jetDes();
	}
	return resultatJet;
}

/**
 * @brief Phase d'achat où le joueur peut acheter une carte
 */
void Jeu::achat(){
// 6e étape de la boucle de jeu. Propose au joueur la liste des cartes achetables
// du Marché, puis appelle la méthode acheter() du Marché.

    // vecteur des cartes achetables par l'utilisateur (monuments et cartes du marché) :
    vector<Carte*> cartesAchetables;

    for (auto &m : joueurActif->getMonuments())
        if (!m->getConstruit())
            cartesAchetables.push_back(m);
        
    for (auto &c : marche->getCarteDispAchat())
        cartesAchetables.push_back(c);
    
    int soldeJoueur = joueurActif->getPieces();
    bool achatEffectue = false;
    Carte* achat;

    while(!achatEffectue){
        Controleur::getControleur()->afficher("\nListe des cartes achetables :\n");
        // on demande au joueur quelle carte il souhaite acheter :
        achat = Controleur::getControleur()->selection_carte(cartesAchetables);

        if(achat != nullptr){
            Controleur::getControleur()->afficher("\nVous avez choisi : " + achat->to_string() + ".\n");
            if(soldeJoueur >= achat->getPrix()){
                achat->acheter();
                joueurActif->perdrePieces(achat->getPrix());
                Controleur::getControleur()->afficher("Achat effectué avec succès.\n");
                achatEffectue = true;
            }else{
                Controleur::getControleur()->afficher("\nVous ne possédez pas assez d'argent pour acheter cette carte. Veuillez en choisir une autre, ou saisir '-1' pour terminer votre tour.\n");
            }
        }else{
            Controleur::getControleur()->afficher("\nVous n'avez rien acheté ce tour-ci.\n");
            achatEffectue = true;
        }
    }
    // Gestion du RSA :
    if (!achatEffectue && soldeJoueur<2){
        joueurActif->gagnerPieces(2-soldeJoueur);
    }
    else if(!achatEffectue && joueurActif->hasAeroport())
        joueurActif->gagnerPieces(10);

    Controleur::getControleur()->afficher("\nFin du tour\n");
    return;
};


void Jeu::activerCartesRouges(int nbDes){
    for (auto &j : joueurs)
        if(&j != joueurActif) //Peut etre que ça marhce pas
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
        if(&j != joueurActif)
        res.push_back(&j);
    }
    return res;
}


