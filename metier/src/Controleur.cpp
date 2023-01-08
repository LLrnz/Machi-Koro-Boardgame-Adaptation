#include "../headers/Controleur.h"
#include "../../gui/headers/dialognouvellepartie.h"
#include "../../gui/headers/windowjeu.h"
#include "../../gui/headers/mainwindow.h"
#include <QApplication>

Controleur::Controleur() {
    wjeu = new WindowJeu();
    interface = new InterfaceTerminal(wjeu->getConsole());
}

Controleur::~Controleur() {
    delete(&wjeu);
    delete(interface);
}

void Controleur::menuPrincipal(){


}


Controleur* Controleur::controleur_ = nullptr;
Controleur* Controleur::getControleur() {
    if (Controleur::controleur_ == nullptr){
        Controleur::controleur_ = new Controleur();
        return controleur_;
    }
    return controleur_;
}

void Controleur::libererControleur() {
    delete controleur_;
    controleur_ = nullptr;
}

void Controleur::afficher(std::string f) const{
    this->interface->afficher(f);
}


std::string Controleur::lire_str(){
    return this->interface->lire();
}

int Controleur::lire_int(int borneInf, int borneSupp){
    return this->interface->lire_int(borneInf, borneSupp);
}


void Controleur::nouvellePartie(){
    DialogNouvellePartie* np = new DialogNouvellePartie();

    np->exec();
    delete np;

    //Vérifier que les joueurs ont bien été initialisés
    //si oui ;
    wjeu->init();
    this->afficher("La partie peut commencer !");
    //Jeu::getJeu().boucleDeJeu();

    //sinon :
    //réouvrir la boite de dialogue




//    //Set up des parametres de la partie
//    map<std::string, TypeJoueur> joueurs;

//    //set up joueurs
//    //nb joueurs
//    this->afficher("Bonjour, combien de joueurs ? ");
//    this->nbJoueurs = this->lire_int(1, 4);

//    //pseudos joueurs
//    for(int i = 0; i < this->nbJoueurs; i++){

//        //Selection type joueur
//        this->afficher("Joueur "+ to_string(i) + " humain (0) ou IA (1) ? ");
//        TypeJoueur type = TypeJoueur::humain;
//        if(this->lire_int(0,1)){
//            type = TypeJoueur::IA;
//        }

//        //Selection pseudo
//        this->afficher("Pseudo joueur "+ to_string(i) +" : ");
//        std::string pseudo = this->lire_str();

//        //insertion joueur dans la map
//        joueurs[pseudo] = type;
//    }

//    //set up extensions

//    auto ext = {Extensions::marina, Extensions::deluxe};
//    string enumExt[] {"harbour", "deluxe"};
//    for( const auto e : ext ){
//        this->afficher("Jouer avec l'extension " + enumExt[static_cast<int>(e)-1] + " ? ");
//        bool val = this->lire_int(0,1);
//        this->extensions.emplace(e, val);

//    }
//    this->extensions.emplace(Extensions::base, true);
//    Jeu::getJeu().genererPartie(joueurs, extensions);


}

void Controleur::demarrer(){
//    Jeu::getJeu().boucleDeJeu();
}

Joueur* Controleur::selection_joueur(vector<Joueur*> joueurs){
    return this->interface->selection_joueur(joueurs);
}

Batiment* Controleur::selection_batiment(vector<Batiment*> batiments){
    return this->interface->selection_batiment(batiments);
}

void  Controleur::afficher(vector<Joueur*> joueurs){
    this->interface->afficher(joueurs);
}
void  Controleur::afficher(vector<Batiment*> batiments){
    this->interface->afficher(batiments);
}

