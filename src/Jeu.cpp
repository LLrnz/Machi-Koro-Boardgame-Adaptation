#include "../headers/Controleur.h"

#include "headers/CarteBleue.h"
#include "headers/CarteVerte.h"
#include "headers/CarteViolette.h"
#include "headers/CarteRouge.h"
#include "services.cpp"
#include <QtCore>
#include <iostream>
#include <cstdlib>
#include <sstream>


using namespace std;

/**
 * Constructeur de jeu
 * @brief Jeu::Jeu
 */
Jeu::Jeu():cartesEnJeu(), joueurs(), joueurActif(nullptr), marche(nullptr){

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
    for (Batiment* c : cartesEnJeu) {
        std::cout << c->getNom() << std::endl;
    }
}


//Qu'est ce que c'es que ça ??? edit : ok lol j'ai compris d'où venait le bug
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
    Controleur::getControleur()->afficher("C'est a " + joueurActif->getPseudo() + " de jouer ! \n");

    Controleur::getControleur()->afficher(joueurActif->getConstructions());
    Controleur::getControleur()->afficher("\n");

	int resultatJet = jeu->lancerDes();
    Controleur::getControleur()->afficher("Vous avez " + to_string(joueurActif->getPieces()) + " pièces ! \n");

	jeu->activerCartesRouges(resultatJet);
	jeu->activerCartesBleues(resultatJet);
	jeu->activerCartesVertes(resultatJet);
	jeu->activerCartesViolettes(resultatJet);
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
			int de1 = rand() % 6;
			int de2 = rand() % 6;   
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
			resultatJet = (rand() % 6);
	}
    //le joueur n'a pas le choix de lancer 1 dé
	else
		resultatJet = (rand() % 6);

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
    stringstream s;
    for (Monument m : joueurActif->getMonuments()){
        if (!m.getConstruit()){
            monumentsAchetables.push_back(&m);
            s << "  " << i << " : " << m.getNom() << " (" << m.getPrix() << ")\n";
            i++;
        }
    }
    Controleur::getControleur()->afficher(s.str());

    // on récupère le solde actuel du joueur :
    int soldeJoueur = joueurActif->getPieces();

    // on demande au joueur quelle carte il souhaite acheter :
    Controleur::getControleur()->afficher("Saisir le numéro de la carte que vous souhaitez acheter, et -1 si vous n'achetez rien : ");
    bool achatEffectue = false;
    string rep;
    while(!achatEffectue){
        rep = Controleur::getControleur()->lire_str();
        int num = stoi(rep);

        // s'il n'achète rien
        if (num==-1) break; 
        
        // si la carte demandée est un batiement du marché :
        if (num<10){
            if (batimentsAchetables[num]->getPrix() > soldeJoueur)
                Controleur::getControleur()->afficher("\nVous ne possédez pas assez d'argent pour acheter cette carte. Veuillez en choisir une autre, ou saisir 'R' pour terminer votre tour.\n");
            else{
                // si le joueur a assez d'argent pour acheter la carte :
                achatEffectue = true;
                // on enlève la carte du marché
                Batiment* c = marche->acheter(num);
                // on la donne au joueur
                joueurActif->ajouterBatiment(c);
                // et on actualise son solde
                joueurActif->perdrePieces(batimentsAchetables[num]->getPrix());
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
                joueurActif->perdrePieces(batimentsAchetables[num]->getPrix());
                Controleur::getControleur()->afficher("Achat effectué avec succès.\n");
            }
        }
    }

    // Gestion du RSA :
    if (!achatEffectue && soldeJoueur<2){
        joueurActif->gagnerPieces(2-soldeJoueur);
    }
    if(!achatEffectue && joueurActif->hasAeroport())
        joueurActif->gagnerPieces(10);

    Controleur::getControleur()->afficher("Fin du tour");
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



//A METTRE DANS UNE AUTRE CLASSE
void Jeu::initialiserCartes(map<Extensions, bool> extensions) {
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
            cartesEnJeu.push_back(new CarteBleue(id, nom, type, prix, gain, combinaisons,Couleur::Bleu));
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
            cartesEnJeu.push_back(new CarteVerte(id, nom, type, prix, gain, combinaisons,Couleur::Vert, TypeBatiment::ble));
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
            cartesEnJeu.push_back(new CarteRouge(id, nom, type, prix, gain, combinaisons,Couleur::Rouge, 2));
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
            cartesEnJeu.push_back(new CarteViolette(id, nom, type, prix, gain, combinaisons, Couleur::Violet));
            id += 1;
        }
    }
}


