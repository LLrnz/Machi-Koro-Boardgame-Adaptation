#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include "../headers/Joueur.h"
#include <cstdlib> 


Jeu* Jeu::jeu = nullptr;
Jeu& Jeu::getJeu() {
	if (jeu == nullptr)
		jeu = new Jeu;
	return *jeu;
}

void Jeu::libererJeu() {
	delete jeu;
	jeu = nullptr;
}


void Jeu::initialiserJoueurs() {
	for (int i = 0; i < Controleur::getControleur().getNbJoueurs(); i++) {
		joueurs.push_back(Joueur(Controleur::getControleur().getPseudo(i), Controleur::getControleur().getTypeJoueur(i)));
	}
}

void Jeu::joueurSuivant() {
	if (Jeu::getJeu().getJoueurActif() == size(joueurs) - 1)
		Jeu::getJeu().setJoueurActif(1);
	else
		joueurActif += 1;

};

void Jeu::genererPartie() {
	Jeu::getJeu().initialiserJoueurs();
	Jeu::getJeu().initialiserCartes();
}

void Jeu::boucleDeJeu() {
	while (Jeu::getJeu().getPartieTerminee() == false) {
		Jeu::getJeu().joueurSuivant();
		Jeu::getJeu().tourDeJeu();
	}
	
	Controleur::getControleur().afficher("Le joueur ");
	Controleur::getControleur().afficher(Jeu::getJeu().getJoueurActif());
	Controleur::getControleur().afficher("a gagne la partie ! \n");
	//std::ostream& f = std::cout;
	//f << "Le joueur " << Jeu::getJeu().getJoueurActif() << "a gagne la partie ! \n";
	//Controleur::getControleur().afficher(f);

}

void Jeu::tourDeJeu() {
	std::cout << "C'est a " << Controleur::getControleur().getPseudo(Jeu::getJeu().getJoueurActif()) << "de jouer ! \n";
	Jeu::getJeu().lancerDes();

}

int Jeu::jetDes(){
	int resultatJet;
	if (Jeu::getJeu().getJoueurs()[joueurActif].hasDoubleDes() == true){
		Controleur::getControleur().afficher("1 : Lancer un de \n");
		Controleur::getControleur().afficher("2 : Lancer deux des \n");
		string reponse;
		reponse = Controleur::getControleur().lire();
		if (std::stoi(reponse) == 2){
			int de1 = rand() % 6;
			int de2 = rand() % 6;
			resultatJet = de1 + de2;
			if (de1 == de2){
				Controleur::getControleur().afficher("Le resultat est un double, vous rejouez un tour apres celui ci ! \n");
				Jeu::getJeu().getJoueurs()[joueurActif].setRejoueTour(true);
			}
			else
				Jeu::getJeu().getJoueurs()[joueurActif].setRejoueTour(false);
		}
		else
			resultatJet = (rand() % 6);
	}
	else
		resultatJet = (rand() % 6);
	if ((resultatJet >= 10) && (Jeu::getJeu().getJoueurs()[joueurActif].hasPort())){
		Controleur::getControleur().afficher("Le resultat est superieur a 10 ! \n");
		Controleur::getControleur().afficher("Le resultat du jet est ");
		Controleur::getControleur().afficher(resultatJet);
		Controleur::getControleur().afficher("1 : Ne pas ajouter 2 au resultat \n");
		Controleur::getControleur().afficher("2 : Ajouter 2 au resultat \n");
		string rep;
		rep = Controleur::getControleur().lire();
		if (std::stoi(rep) == 2)
			resultatJet += 2;
	}
	Controleur::getControleur().afficher("Le resultat du jet est ");
	Controleur::getControleur().afficher(resultatJet);
	Controleur::getControleur().afficher("\n");
	return resultatJet;
}

int Jeu::lancerDes(){
	int resultatJet = jetDes();
	if (Jeu::getJeu().getJoueurs()[joueurActif].hasRelancerDes()){
		Controleur::getControleur().afficher("1 : Ne pas relancer les des \n");
		Controleur::getControleur().afficher("2 : Relancer les des \n");
		string reponse;
		reponse = Controleur::getControleur().lire();
		if (std::stoi(reponse) == 2)
			resultatJet = jetDes();
	}
	return resultatJet;
}