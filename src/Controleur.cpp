#include "../headers/Controleur.h"
Controleur* Controleur::controleur = nullptr;
Controleur& Controleur::getControleur() {
	if (controleur == nullptr)
		controleur = new Controleur;
	return *controleur;
}

void Controleur::libererControleur() {
	delete controleur;
	controleur = nullptr;
}

void Controleur::afficher(string s) {
	interface.afficher(s);
}
void Controleur::afficher(int i) {
	interface.afficher(i);
}
string& Controleur::lire(){
	return interface.lire();
}