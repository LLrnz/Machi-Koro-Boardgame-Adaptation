#include "../headers/Controleur.h"

Controleur::Controleur():interface(InterfaceTerminal()) {
}

Controleur::~Controleur() {}

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
    this->interface.afficher(f);
}


std::string Controleur::lire_str(){
    return this->interface.lire();
}

int Controleur::lire_int(int borneInf, int borneSupp){
    return this->interface.lire_int(borneInf, borneSupp);
}


void Controleur::nouvellePartie(){
    //Set up des parametres de la partie
    map<std::string, TypeJoueur> joueurs;

    //set up joueurs
    //nb joueurs
    this->afficher("Bonjour, combien de joueurs ?");
    this->nbJoueurs = this->lire_int(1, 4);

    //pseudos joueurs
    for(int i = 0; i < this->nbJoueurs; i++){

        //Selection type joueur
        this->afficher("Joueur "+ to_string(i) + " humain (0) ou IA (1) ?");
        TypeJoueur type = TypeJoueur::humain;
        if(this->lire_int(0,1)){
            type = TypeJoueur::IA;
        }

        //Selection pseudo
        this->afficher("Pseudo joueur "+ to_string(i) +" :");
        std::string pseudo = this->lire_str();

        //insertion joueur dans la map
        joueurs[pseudo] = type;
    }

    //set up extensions
    for( const auto e : {Extensions::marina, Extensions::deluxe} ){
        this->afficher("Jouer avec l'extension ? ");
        bool val = this->lire_int(0,1);
        this->extensions.emplace(e, val);

    }
    this->extensions.emplace(Extensions::base, true);
    Jeu::getJeu().genererPartie(joueurs, extensions);


}

void Controleur::demarrer(){
    Jeu::getJeu().boucleDeJeu();
}

Joueur* Controleur::selection_joueur(vector<Joueur*> joueurs){
    return this->interface.selection_joueur(joueurs);
}

Batiment* Controleur::selection_batiment(vector<Batiment*> batiments){
    return this->interface.selection_batiment(batiments);
}

void  Controleur::afficher(vector<Joueur*> joueurs){
     this->interface.afficher(joueurs);
}
void  Controleur::afficher(vector<Batiment*> batiments){
    this->interface.afficher(batiments);
}

