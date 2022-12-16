#include "headers/Jeu.h"
#include "headers/CarteBleue.h"
#include "headers/CarteRouge.h"
#include "headers/CarteVerte.h"
#include "headers/CarteViolette.h"
#include "headers/Controleur.h"
#include "headers/Joueur.h"
#include "services.cpp"
#include <QtCore>
#include <iostream>
#include <cstdlib> 

void Jeu::initialiserCartes() {
    QByteArray val;
    QFile file(":/cartes/cartes.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Impossible d'accéder au fichier" << std::endl;
    }
    val = file.readAll();
    file.close();
    QJsonDocument fichierCarte = QJsonDocument::fromJson(val);
    QJsonObject objFichierCarte = fichierCarte.object();
    QJsonValue data = objFichierCarte.value(QString("cartes"));
    QJsonObject item = data.toObject();


    int id = 0;
    QJsonObject lstCarteBleue = item.value(QString("bleu")).toObject();
    for(const QString& key: lstCarteBleue.keys()) {
        QJsonObject value = lstCarteBleue.value(key).toObject();

        std::string nom = value.value("nom").toString().toStdString();
        int prix = value.value("prix").toInt();
        int quantite = value.value("quantite").toInt();
        std::string otype = value.value("type").toString().toStdString();
        QJsonValue activation = value.value("activation");

        int gain = activation.toObject().value("gain").toInt();

        std::vector<int> combinaisons;
        for (QJsonValueRef combi : activation.toObject().value("nb").toArray()) {
            combinaisons.push_back(combi.toInt());
        }
        TypeBatiment type = determineType(otype);


        for (int i = 0; i < quantite; i++) {
            cartesEnJeu.push_back(new CarteBleue(id, nom, type, prix, gain, combinaisons,Couleur::bleu));
            id += 1;
        }

    }

    // Parcours de la liste des cartes vertes
    // On récupère les informations de chaque carte
    // On les stocke dans un vecteur de cartes
    QJsonObject lstCarteVerte = item.value(QString("verte")).toObject();
    for(const QString& key: lstCarteVerte.keys()) {
        QJsonObject value = lstCarteVerte.value(key).toObject();

        std::string nom = value.value("nom").toString().toStdString();
        int prix = value.value("prix").toInt();
        int quantite = value.value("quantite").toInt();
        std::string otype = value.value("type").toString().toStdString();
        QJsonValue activation = value.value("activation");

        int gain = activation.toObject().value("gain").toInt();

        std::vector<int> combinaisons;
        for (QJsonValueRef combi : activation.toObject().value("nb").toArray()) {
            combinaisons.push_back(combi.toInt());
        }
        TypeBatiment type = determineType(otype);

        for (int i = 0; i < quantite; i++) {
            cartesEnJeu.push_back(new CarteVerte(id, nom, type, prix, gain, combinaisons,Couleur::vert, TypeBatiment::ble));
            //cartesEnJeu.push_back(new CarteVerte(id, nom, type, prix, gain, combinaisons,Couleur::vert, effectType));
            id += 1;
        }
    }

    // Parcours de la liste des cartes rouges
    // On récupère les informations de chaque carte
    // On les stocke dans un vecteur de cartes
    QJsonObject lstCarteRouge = item.value(QString("rouge")).toObject();
    for(const QString& key: lstCarteRouge.keys()) {
        QJsonObject value = lstCarteRouge.value(key).toObject();

        std::string nom = value.value("nom").toString().toStdString();
        int prix = value.value("prix").toInt();
        int quantite = value.value("quantite").toInt();
        std::string otype = value.value("type").toString().toStdString();
        QJsonValue activation = value.value("activation");

        int gain = activation.toObject().value("gain").toInt();

        std::vector<int> combinaisons;
        for (QJsonValueRef combi : activation.toObject().value("nb").toArray()) {
            combinaisons.push_back(combi.toInt());
        }
        TypeBatiment type = determineType(otype);

        for (int i = 0; i < quantite; i++) {
            cartesEnJeu.push_back(new CarteRouge(id, nom, type, prix, gain, combinaisons,Couleur::rouge, 2));
            //cartesEnJeu.push_back(new CarteRouge(id, nom, type, prix, gain, combinaisons,Couleur::rouge, nbMonuToActivate));
            id += 1;
        }
    }

    // Parcours de la liste des cartes violettes
    // On récupère les informations de chaque carte
    // On les stocke dans un vecteur de cartes
    // Les cartes violettes ont un attribut en plus nommé "source"
    QJsonObject lstCarteViolette = item.value(QString("violet")).toObject();
    for(const QString& key: lstCarteViolette.keys()) {
        QJsonObject value = lstCarteViolette.value(key).toObject();

        std::string nom = value.value("nom").toString().toStdString();
        int prix = value.value("prix").toInt();
        int quantite = value.value("quantite").toInt();
        std::string otype = value.value("type").toString().toStdString();
        QJsonValue activation = value.value("activation");

        int gain = activation.toObject().value("gain").toInt();

        std::vector<int> combinaisons;
        for (QJsonValueRef combi : activation.toObject().value("nb").toArray()) {
            combinaisons.push_back(combi.toInt());
        }
        TypeBatiment type = determineType(otype);

        //std::string source = activation.toObject().value("source").toString().toStdString();
        //Source typeSource = determineSource(source);

        for (int i = 0; i < quantite; i++) {
            cartesEnJeu.push_back(new CarteViolette(id, nom, type, prix, gain, combinaisons, Couleur::violet));
            id += 1;
        }
    }
}

Jeu::Jeu() {
    initialiserCartes();
}

Jeu::~Jeu() {
    for (Carte* c : cartesEnJeu) {
        delete c;
    }
}

void Jeu::afficherCartes() {
    for (Carte* c : cartesEnJeu) {
        std::cout << c->getNom() << std::endl;
    }
}



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
    for (int i = 0; i < Controleur::getControleur()->getNbJoueurs(); i++) {
        joueurs.push_back(Joueur(Controleur::getControleur()->getPseudo(i), Controleur::getControleur()->getTypeJoueur(i)));
	}
}

void Jeu::joueurSuivant() {
    if (joueurActif == static_cast<int>(size(joueurs)) - 1)
		joueurActif = 1;
	else
		joueurActif += 1;

};

void Jeu::genererPartie() {
	jeu->initialiserJoueurs();
	jeu->initialiserCartes();
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
    std::cout << "C'est a " << Controleur::getControleur()->getPseudo(joueurActif) << "de jouer ! \n";
	int resultatJet = jeu->lancerDes();
	jeu->activerCartesRouges(resultatJet);
	jeu->activerCartesBleues(resultatJet);
	jeu->activerCartesVertes(resultatJet);
	jeu->activerCartesViolettes(resultatJet);
    //jeu->achat();
    partieTerminee = jeu->verifierVictoire();
}

bool Jeu::verifierVictoire(){
    vector<bool> extensions = Controleur::getControleur()->getExtensions();
    if (extensions[1] == 1 || extensions[2] == 1){
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
        reponse = Controleur::getControleur()->lire();
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
        Controleur::getControleur()->afficher(resultatJet);
        Controleur::getControleur()->afficher("1 : Ne pas ajouter 2 au resultat \n");
        Controleur::getControleur()->afficher("2 : Ajouter 2 au resultat \n");
		string rep;
        rep = Controleur::getControleur()->lire();
		if (std::stoi(rep) == 2)
			resultatJet += 2;
	}
    Controleur::getControleur()->afficher("Le resultat du jet est ");
    Controleur::getControleur()->afficher(resultatJet);
    Controleur::getControleur()->afficher("\n");
	return resultatJet;
}

int Jeu::lancerDes(){
	int resultatJet = jetDes();
    if (joueurs[joueurActif].hasTourRadio()){
        Controleur::getControleur()->afficher("1 : Ne pas relancer les des \n");
        Controleur::getControleur()->afficher("2 : Relancer les des \n");
		string reponse;
        reponse = Controleur::getControleur()->lire();
		if (std::stoi(reponse) == 2)
			resultatJet = jetDes();
	}
	return resultatJet;
}

void Jeu::activerCartesRouges(int nbDes){
    for (size_t i = joueurActif-1;i>joueurActif-sizeof(jeu->getJoueurs());i--)
		joueurs[i].activerCartesRouges(nbDes);
}
void Jeu::activerCartesBleues(int nbDes){
    for (size_t i = 0;i<sizeof(jeu->getJoueurs());i++)
		joueurs[i].activerCartesBleues(nbDes);
}
void Jeu::activerCartesVertes(int nbDes){
    joueurs[joueurActif].activerCartesVertes(nbDes);
}
void Jeu::activerCartesViolettes(int nbDes){
    joueurs[joueurActif].activerCartesViolettes(nbDes);
}

