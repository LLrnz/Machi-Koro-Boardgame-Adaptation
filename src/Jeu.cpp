#include "../headers/Jeu.h"
#include "../headers/Controleur.h"
#include "../headers/Joueur.h"


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
