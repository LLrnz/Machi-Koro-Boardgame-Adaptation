#include "../headers/Jeu.h"
#include "../headers/CarteBleue.h"
#include "../headers/CarteRouge.h"
#include "../headers/CarteVerte.h"
#include "../headers/CarteViolette.h"
#include "../headers/Controleur.h"
#include "../headers/Joueur.h"
#include "../headers/marche.h"
#include "services.cpp"
#include <QtCore>
#include <iostream>
#include <cstdlib>
#include <sstream>


using namespace std;

void Jeu::initialiserCartes(map<Extensions, bool> extensions) {
    services::chargerFichier(cartesEnJeu, extensions); // charger le fichier json
    
}
    
Jeu::Jeu():joueurActif(0),marche(nullptr) {
    //initialiserCartes();

    this->controleur = Controleur::getControleur();
}

Jeu::~Jeu() {
    delete marche;
    for (Batiment* c : cartesEnJeu) {
        delete c;
    }
}

void Jeu::afficherCartes() {
    for (Batiment* c : cartesEnJeu) {
        std::cout << c->getNom() << std::endl;
    }
}



Jeu* Jeu::jeu = nullptr;

Jeu* Jeu::getJeu() {
    if (Jeu::jeu == nullptr){
        Jeu::jeu = new Jeu;
        return jeu;
    }
    return jeu;
}

void Jeu::libererJeu() {
	delete jeu;
	jeu = nullptr;
}


void Jeu::initialiserJoueurs(map<std::string, TypeJoueur> listeJoueurs) {
    for (const auto &j : listeJoueurs) {
        std::string pseudo = j.first;
        TypeJoueur type = j.second;
        joueurs.push_back(Joueur(pseudo, type));
	}
}

void Jeu::joueurSuivant() {
    joueurActif = ++joueurActif%joueurs.size();
    //if (joueurActif == joueurs.size()-1)
    //	joueurActif = 0;
    //else
    //	joueurActif += 1;

};

void Jeu::genererPartie(map<std::string, TypeJoueur> listeJoueurs, map<Extensions, bool> extensions) {
    this->initialiserJoueurs(listeJoueurs);
    this->initialiserCartes(extensions);
    marche = new Marche(cartesEnJeu);
}

void Jeu::boucleDeJeu() {
	while (partieTerminee == false) {
		jeu->joueurSuivant();
		jeu->tourDeJeu();
	}
	
    Controleur::getControleur()->afficher("Le joueur ");
    Controleur::getControleur()->afficher(joueurActif);
    Controleur::getControleur()->afficher("a gagne la partie ! \n");
}

void Jeu::tourDeJeu() {
    controleur->afficher("\n\nC'est a " + getJoueurActif().getPseudo() + " de jouer ! \n");
	int resultatJet = jeu->lancerDes();
	jeu->activerCartesRouges(resultatJet);
	jeu->activerCartesBleues(resultatJet);
	jeu->activerCartesVertes(resultatJet);
	jeu->activerCartesViolettes(resultatJet);
    jeu->achat();
    partieTerminee = jeu->verifierVictoire();
}

bool Jeu::verifierVictoire(){
    bool verifierExtension = false;
    for (const auto &e : controleur->getExtensions())
        if (e.second)
            verifierExtension = true;
    if (verifierExtension){
        int compteur = 0;
        for (size_t i = 0; i<joueurs[joueurActif].getMonuments().size();i++)
            if (joueurs[joueurActif].getMonuments()[i].getConstruit())
                compteur += 1;
        if (compteur >= 5)
            return true;
    }
    else
        if (joueurs[joueurActif].hasGare() && joueurs[joueurActif].hasCentreCommercial() && joueurs[joueurActif].hasParcAttractions() && joueurs[joueurActif].hasTourRadio())
            return true;
    return false;
}

int Jeu::jetDes(){
	int resultatJet;
    if (joueurs[joueurActif].hasGare() == true){
        Controleur::getControleur()->afficher("1 : Lancer un de \n");
        Controleur::getControleur()->afficher("2 : Lancer deux des \n");
		string reponse;
        reponse = Controleur::getControleur()->lire_str();
		if (std::stoi(reponse) == 2){
			int de1 = rand() % 6;
			int de2 = rand() % 6;   
			resultatJet = de1 + de2;
			if (de1 == de2){
                Controleur::getControleur()->afficher("Le resultat est un double, vous rejouez un tour apres celui ci ! \n");
				joueurs[joueurActif].setRejoueTour(true);
			}
			else
				joueurs[joueurActif].setRejoueTour(false);
		}
		else
			resultatJet = (rand() % 6);
	}
	else
		resultatJet = (rand() % 6);
	if ((resultatJet >= 10) && (joueurs[joueurActif].hasPort())){
        Controleur::getControleur()->afficher("Le resultat est superieur a 10 ! \n");
        Controleur::getControleur()->afficher("Le resultat du jet est ");
        Controleur::getControleur()->afficher(to_string(resultatJet));
        Controleur::getControleur()->afficher("1 : Ne pas ajouter 2 au resultat \n");
        Controleur::getControleur()->afficher("2 : Ajouter 2 au resultat \n");
		string rep;
        rep = Controleur::getControleur()->lire_str();
		if (std::stoi(rep) == 2)
			resultatJet += 2;
	}
    Controleur::getControleur()->afficher("Le resultat du jet est ");
    Controleur::getControleur()->afficher(to_string(resultatJet));
    Controleur::getControleur()->afficher("\n");
	return resultatJet;
}

int Jeu::lancerDes(){
	int resultatJet = jetDes();
    if (joueurs[joueurActif].hasTourRadio()){
        Controleur::getControleur()->afficher("1 : Ne pas relancer les des \n");
        Controleur::getControleur()->afficher("2 : Relancer les des \n");
		string reponse;
        reponse = Controleur::getControleur()->lire_str();
		if (std::stoi(reponse) == 2)
			resultatJet = jetDes();
	}
	return resultatJet;
}

void Jeu::extracted(Joueur &joueur, int &i,
                    vector<Monument *> &monumentsAchetables,
                    std::stringstream &s) {
    for (Monument m : joueur.getMonuments()) {
        if (!m.getConstruit()) {
            monumentsAchetables.push_back(&m);
            s << "  " << i << " : " << m.getNom() << " ("
              << m.getPrix() << ")\n";
            i++;
        }
    }
}
void Jeu::achat() {
    // 6e étape de la boucle de jeu. Propose au joueur la liste des cartes
    // achetables du Marché, puis appelle la méthode acheter() du Marché.

    // on récupère le joueur actif :
    Joueur &joueur = getJoueurActif();

    //On affiche les cartes et l'argent du joueur
    for (auto i : joueur.getConstructions())
         Controleur::getControleur()->afficher(i->getNom());

    // affiche la liste des batiments achetables sur le marché :
    vector<Batiment *> batimentsAchetables = marche->getCarteDispAchat();
    Controleur::getControleur()->afficher(
                "\nListe des bâtiments achetables sur le marché :\n");
    int i = 0;
    for (Batiment *c : batimentsAchetables) {
        stringstream s;
        s << "  " << i << " : " << c->getNom() << " (" << c->getPrix()
          << ")\n";
        Controleur::getControleur()->afficher(s.str());
        i++;
    }

    // affiche la liste des monuments achetables par le joueur :
    i = 10; // i=10 correspond donc à monumentsAchetables[0]
    Controleur::getControleur()->afficher(
                "\nListe des monuments non construits :\n");
    vector<Monument *> monumentsAchetables;
    stringstream s;
    extracted(joueur, i, monumentsAchetables, s);
    Controleur::getControleur()->afficher(s.str());

    // on récupère le solde actuel du joueur :
    int soldeJoueur = joueur.getPieces();
    Controleur::getControleur()->afficher("Vous avez ");
    Controleur::getControleur()->afficher(soldeJoueur);

    // on demande au joueur quelle carte il souhaite acheter :
    Controleur::getControleur()->afficher(
                "pièces, saisir le numéro de la carte que vous souhaitez acheter, et -1 si "
                "vous n'achetez rien : ");
    bool achatEffectue = false;
    string rep;
    while (!achatEffectue) {
        rep = Controleur::getControleur()->lire_str();
        int num = stoi(rep);

        // s'il n'achète rien
        if (num == -1)
            break;

        // si la carte demandée est un batiement du marché :
        if (num < 10) {
            if (batimentsAchetables[num]->getPrix() > soldeJoueur)
                Controleur::getControleur()->afficher(
                            "\nVous ne possédez pas assez d'argent "
                            "pour acheter cette carte. Veuillez en "
                            "choisir une autre, ou saisir 'R' pour "
                            "terminer votre tour.\n");
            else {
                // si le joueur a assez d'argent pour acheter la
                // carte :
                achatEffectue = true;
                // on enlève la carte du marché
                Batiment *c = marche->acheter(num);
                // on la donne au joueur
                joueur.ajouterBatiment(c);
                // et on actualise son solde
                joueur.perdrePieces(
                            batimentsAchetables[num]->getPrix());
                Controleur::getControleur()->afficher(
                            "Achat effectué avec succès.\n");
            }
        }
        // si la carte demandée est un monument :
        else if (num >= 10) {
            num -= 10;
            if (monumentsAchetables[num]->getPrix() > soldeJoueur)
                Controleur::getControleur()->afficher(
                            "\nVous ne possédez pas assez d'argent "
                            "pour acheter cette carte. Veuillez en "
                            "choisir une autre, ou saisir 'R' pour "
                            "terminer votre tour.\n");
            else {
                // si le joueur a assez d'argent pour acheter la
                // carte :
                achatEffectue = true;
                // on construit le monument du joueur
                monumentsAchetables[num]->setConstruit();
                // et on actualise son solde
                joueur.perdrePieces(
                            batimentsAchetables[num]->getPrix());
                Controleur::getControleur()->afficher(
                            "Achat effectué avec succès.\n");
            }
        }
    }

    // Gestion du RSA :
    if (!achatEffectue && soldeJoueur < 2) {
        joueur.gagnerPieces(2 - soldeJoueur);
    }
    if (!achatEffectue && joueur.hasAeroport())
        joueur.gagnerPieces(10);

    Controleur::getControleur()->afficher("Fin du tour");
    return;
};

void Jeu::activerCartesRouges(int nbDes){
    for (int i = 0;i<joueurs.size();i++)
        if (joueurActif!=i)
            joueurs[i].activerCartesRouges(nbDes);
}
/*void Jeu::activerCartesBleues(int nbDes){
    for (size_t i = 0;i<sizeof(jeu->getJoueurs());i++)
		joueurs[i].activerCartesBleues(nbDes);
}*/
void Jeu::activerCartesBleues(int nbDes){
    for (auto i : Jeu::getJoueurs())
        i.activerCartesBleues(nbDes);
}

void Jeu::activerCartesVertes(int nbDes){
    joueurs[joueurActif].activerCartesVertes(nbDes);
}
void Jeu::activerCartesViolettes(int nbDes){
    joueurs[joueurActif].activerCartesViolettes(nbDes);
}

