#include "../headers/InterfaceTerminal.h"

InterfaceTerminal::InterfaceTerminal(){

}


void InterfaceTerminal::afficher(std::string f) const{
    std::cout << f;
}

std::string InterfaceTerminal::lire() const{
    std::string res;
    std::cin >> res;
    return res;
}

int InterfaceTerminal::lire_int(){
    bool chiffre = false;
    int res;
    while (!chiffre){
        std::string str = this->lire();

       try {
            res = std::stoi(str);
            chiffre = true;
       }catch (...) {
            std::cout << "Merci d'entrer un chiffre.";
       }
    }
    return res;
}

int InterfaceTerminal::lire_int(int x, int y){
    bool bornesOk = false;
    int res;
    while(!bornesOk){
        res = this->lire_int();
        if(((res >= x) && (res <= y))){
            bornesOk = true;
        }else{
           std::cout << "Merci d'entrer un chiffre entre " << x << " et " << y << ".";
        }
    }
    return res;
}

void InterfaceTerminal::afficher(vector<Joueur*> joueurs){
    int cpt = 1;
    for(const auto &j : joueurs){
        std::cout << cpt << " : " << j->getPseudo() << "(" << j->getPieces() << "pièces) \n";
    }
    cpt++;
}

void InterfaceTerminal::afficher(vector<Batiment*> batiments){
    int cpt = 1;
    for(const auto &b : batiments){
        std::cout << cpt << " : " << b->to_string() << "\n";
    }
    cpt++;
}

Joueur* InterfaceTerminal::selection_joueur_batiment(vector<Joueur*> joueurs){
    for(auto &j : joueurs){
           afficher(j->to_string());
           afficher(j->getConstructions());
    }
    int choix = lire_int(-1, joueurs.size()-1);
    Joueur* res = nullptr;
    bool valide = false;

    if( choix != -1){
        while(!valide){
            try {
                res = joueurs.at(choix);
                valide = true;
            } catch (...) {
                std::cout << "joueur inexistant";
            }
        }
    }

    return res;
}

Joueur* InterfaceTerminal::selection_joueur(vector<Joueur*> joueurs){
    afficher(joueurs);
    int choix = lire_int(0, joueurs.size()-1);
    Joueur* res;
    bool valide = false;

    while(!valide){
        try {
            res = joueurs.at(choix);
            valide = true;
        } catch (...) {
            std::cout << "joueur inexistant";
        }
    }


    return res;
}

/**
 * @brief InterfaceTerminal::selection_batiment
 * @param batiments
 * @return
 */
Batiment* InterfaceTerminal::selection_batiment(vector<Batiment*> batiments){
    afficher(batiments);
    int choix = lire_int(0, batiments.size()-1);
    Batiment* res;
    bool valide = false;

    while(!valide){
        try {
            res = batiments.at(choix);
            valide = true;
        } catch (...) {
            std::cout << "Batiment inexistant";
        }
    }


    return res;
}


/**
 * @brief InterfaceTerminal::changerCouleur
 * @param 0 = Black | 1 = Blue | 8 = Gray | 9 = Light Blue | 2 = Green | a = Light Green | 3 = Aqua | b = Light Aqua | 4 = Red |c = Light Red | 5 = Purple | d = Light Purple | 6 = Yellow | e = Light Yellow | 7 = White | f = Bright White
 *
 */

void InterfaceTerminal::changerCouleur(char couleur_texte, char couleur_fond){
    std::string c = "color ";
    c += couleur_fond;
    c += couleur_texte;
    system(c.c_str());
}
