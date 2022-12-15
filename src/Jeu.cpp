#include "../headers/Jeu.h"
#include "../headers/CarteBleue.h"
#include "../headers/CarteRouge.h"
#include "../headers/CarteVerte.h"
#include "../headers/CarteViolette.h"
#include "../headers/Controleur.h"
#include "../headers/Joueur.h"
#include "../headers/Marche.h"
#include "services.cpp"
#include <QtCore>
#include <iostream>
#include <cstdlib>
#include <sstream>


using namespace std;

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

    // Parcours de la liste des cartes bleues
    // On récupère les informations de chaque carte
    // On les stocke dans un vecteur de cartes
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
            cartesEnJeu.push_back(new CarteBleue(id, nom, type, prix, gain, combinaisons));
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
            cartesEnJeu.push_back(new CarteVerte(id, nom, type, prix, gain, combinaisons));
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
            cartesEnJeu.push_back(new CarteRouge(id, nom, type, prix, gain, combinaisons));
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

        std::string source = activation.toObject().value("source").toString().toStdString();
        Source typeSource = determineSource(source);

        for (int i = 0; i < quantite; i++) {
            cartesEnJeu.push_back(new CarteViolette(id, nom, type, prix, gain, combinaisons, typeSource));
            id += 1;
        }
    }
}
    
Jeu::Jeu():marche(nullptr) {
    initialiserCartes();
    marche = new Marche(cartesEnJeu);
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
    if (Jeu::getJeu().getIndiceJoueurActif() == static_cast<int>(size(joueurs)) - 1)
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
	
    Controleur::getControleur()->afficher("Le joueur ");
    Controleur::getControleur()->afficher(Jeu::getJeu().getIndiceJoueurActif());
    Controleur::getControleur()->afficher("a gagne la partie ! \n");
	//std::ostream& f = std::cout;
	//f << "Le joueur " << Jeu::getJeu().getJoueurActif() << "a gagne la partie ! \n";
	//Controleur::getControleur().afficher(f);

}

void Jeu::tourDeJeu() {
    std::cout << "C'est a " << Controleur::getControleur()->getPseudo(Jeu::getJeu().getIndiceJoueurActif()) << "de jouer ! \n";
	Jeu::getJeu().lancerDes();

}

int Jeu::jetDes(){
	int resultatJet;
	if (Jeu::getJeu().getJoueurs()[joueurActif].hasDoubleDes() == true){
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
	if (Jeu::getJeu().getJoueurs()[joueurActif].hasRelancerDes()){
        Controleur::getControleur()->afficher("1 : Ne pas relancer les des \n");
        Controleur::getControleur()->afficher("2 : Relancer les des \n");
		string reponse;
        reponse = Controleur::getControleur()->lire();
		if (std::stoi(reponse) == 2)
			resultatJet = jetDes();
	}
	return resultatJet;
}


void Jeu::achat(){
// 6e étape de la boucle de jeu. Propose au joueur la liste des cartes achetables 
// du Marché, puis appelle la méthode acheter() du Marché.

    // on récupère le joueur actif :
    Joueur joueur = getJoueurActif();

    // affiche la liste des batiments achetables sur le marché :
    vector<Batiment*> batimentsAchetables = marche->getCarteDispAchat();
    Controleur::getControleur()->afficher("\nListe des bâtiments achetables sur le marché :");
    int i = 0;
    for (Batiment* c : batimentsAchetables){
        stringstream s;
        s << "  " << i << " : " << c->getNom() << " (" << c->getPrix() << ")\n";
        Controleur::getControleur()->afficher(s.str());
        i++;
    }
    
    // affiche la liste des monuments achetables par le joueur :
    i = 10;  // i=10 correspond donc à monumentsAchetables[0]
    Controleur::getControleur()->afficher("\nListe des monuments non construits :");
    vector<Monument*> monumentsAchetables; 
    for (Monument m : joueur.getMonuments()){
        if (!m.getConstruit()){
            monumentsAchetables.push_back(&m);
            stringstream s;
            s << "  " << i << " : " << m.getNom() << " (" << m.getPrix() << ")\n";
            Controleur::getControleur()->afficher("\nListe des monuments :");
            i++;
        }
    }

    // on récupère le solde actuel du joueur :
    int soldeJoueur = joueur.getPieces();

    // on demande au joueur quelle carte il souhaite acheter :
    Controleur::getControleur()->afficher("Saisir le numéro de la carte que vous souhaitez acheter, et -1 si vous n'achetez rien : ");
    bool achatEffectue = false;
    string rep;
    while(!achatEffectue){
        rep = Controleur::getControleur()->lire();
        int num = stoi(rep);

        // s'il n'achète rien
        if (num==-1) break; // on quitte le while en gardant achatEffectue=False
        
        // si la carte demandée est un batiment du marché :
        if (num<10){
            if (batimentsAchetables[num]->getPrix() > soldeJoueur)
                Controleur::getControleur()->afficher("\nVous ne possédez pas assez d'argent pour acheter cette carte. Veuillez en choisir une autre, ou saisir 'R' pour terminer votre tour.\n");
            else{
                // si le joueur a assez d'argent pour acheter la carte :
                achatEffectue = true;
                // on enlève la carte du marché
                Batiment* c = marche->acheter(num);
                // on la donne au joueur
                joueur.ajouterBatiment(c);
                // et on actualise son solde
                joueur.perdrePieces(batimentsAchetables[num]->getPrix());
                Controleur::getControleur()->afficher("Achat effectué avec succès.\n");
            }
        }

        // si la carte demandée est un monument :
        else if (num>=10){
            num-=10;
            if (monumentsAchetables[num]->getPrix() > soldeJoueur)
                Controleur::getControleur()->afficher("\nVous ne possédez pas assez d'argent pour acheter cette carte. Veuillez en choisir une autre, ou saisir 'R' pour terminer votre tour.\n");
            else{
                // si le joueur a assez d'argent pour acheter la carte :
                achatEffectue = true;
                // on construit le monument du joueur
                monumentsAchetables[num]->setConstruit();
                // et on actualise son solde
                joueur.perdrePieces(batimentsAchetables[num]->getPrix());
                Controleur::getControleur()->afficher("Achat effectué avec succès.\n");
            }
        }
    }

    // Gestion du RSA :
    if (!achatEffectue && soldeJoueur<2){
        joueur.gagnerPieces(2-soldeJoueur);
    }

    Controleur::getControleur()->afficher("Fin du tour");
    return;
};
