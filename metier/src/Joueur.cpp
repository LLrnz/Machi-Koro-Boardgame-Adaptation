#include "../headers/Joueur.h"
#include "../headers/enums.h"
#include "../headers/Controleur.h"
#include "../headers/CartesMonuments.h"
#include "../headers/cartesbleues.h"
#include<bits/stdc++.h>

/*!
 * \brief Constructeur
 * \param pseudo du joueur
 * \param type (IA/Humain)
 */
Joueur::Joueur(std::string psdo, TypeJoueur typ) : type(typ), pseudo(psdo), pieces(3), rejoueTour(false), batiments(){
    auto extensions = Controleur::getControleur()->getExtensions();
    if (extensions[Extensions::marina] || extensions[Extensions::deluxe])
        monuments = {new Port("Port",2), new Gare("Gare",4), new CentreCommercial("Centre commercial",10), new ParcDattraction("Parc d'attractions",16), new TourRadio("Tour radio",22), new Aeroport("Aeroport",30)};
    else
        monuments = {new Gare("Gare",4), new CentreCommercial("Centre commercial",10), new ParcDattraction("Parc d'attractions",16), new TourRadio("Tour radio",22)};

}

/*!
 * \brief le joueur a-t-il construit le port
 * \return
 */
bool Joueur::hasPort() const {
    bool has = false;
    for (const auto &i : monuments)
        if (i->getNom()=="Port" && i->getConstruit())
            has = true;
    return has;
}

/*!
 * \brief le joueur a-t-il construit la gare
 * \return
 */
bool Joueur::hasGare() const {
    bool has = false;
    for (const auto &i : monuments)
        if (i->getNom()=="Gare" && i->getConstruit())
            has = true;
    return has;
}

/*!
 * \brief le joueur a-t-il construit le centre commercial
 * \return
 */
bool Joueur::hasCentreCommercial() const {
    bool has = false;
    for (const auto &i : monuments)
        if (i->getNom()=="Centre commercial" && i->getConstruit())
            has = true;
    return has;
}

bool Joueur::hasParcAttractions() const{
    bool has = false;
    for (const auto &i : monuments)
        if (i->getNom()=="Parc d'attractions" && i->getConstruit())
            has = true;
    return has;
}

bool Joueur::hasTourRadio() const {
    bool has = false;
    for (const auto &i : monuments)
        if (i->getNom()=="Tour radio" && i->getConstruit())
            has = true;
    return has;
}


/*!
 * \brief le joueur a-t-il construit l'aéroport
 * \return
 */
bool Joueur::hasAeroport() const{
    bool has = false;
    for (const auto &i : monuments)
        if (i->getNom()=="Aeroport" && i->getConstruit())
            has = true;
    return has;
}


/*!
 * \brief permet de faire perdre despièces à un joueur
 * \param le nombre de pièces à perdre
 * \return le nombre de pièces perdu réel
 */
int Joueur::perdrePieces(int nb){
// Soustrait le nombre nb de pièces au joueur et retourne le nombre de pièces 
// réellement soustraites (un joueur ne peut pas avoir un nombre négatif de pièces).

    if (pieces - nb < 0){ // si le joueur doit perdre plus d'argent qu'il n'en a
        int tmp = pieces;
        pieces = 0;    // ben il est fauché
        return tmp; // et on retourne ce qu'il avait (=ce qu'il a perdu)
    }

    pieces -= nb; // sinon, on diminue son solde 
    return nb; // et on retourne ce qu'il a perdu
};

/*!
 * \brief active les cartes bleues du joueur correspondant au nbDes
 * \param nbDes
 */
void Joueur::activerCartesBleues(int nbDes){
    for (auto &it : batiments){
        bool bonNombreAuDe = false;
        for (auto &it2 : it->getCombinaisons())
            if (it2 == nbDes) { bonNombreAuDe = true;}
        if (it->getCouleur()==Couleur::Bleu && bonNombreAuDe)
             it->activer(this);
    }
}

/*!
 * \brief active les cartes vertes du joueur correspondant au nbDes
 * \param nbDes
 */
void Joueur::activerCartesVertes(int nbDes){
    for (auto &it : batiments){
        bool bonNombreAuDe = false;
        for (auto &it2 : it->getCombinaisons() )
            if (it2 == nbDes) { bonNombreAuDe = true;}

        if (it->getCouleur()==Couleur::Vert && bonNombreAuDe)
            it->activer(this);
    }
}

/*!
 * \brief active les cartes rouges du joueur correspondant au nbDes
 * \param nbDes
 */
void Joueur::activerCartesRouges(int nbDes){
    for (auto &it : batiments){
        bool bonNombreAuDe = false;
        for (auto &it2 : it->getCombinaisons())
            if (it2 == nbDes) { bonNombreAuDe = true;}
        if (it->getCouleur()==Couleur::Rouge && bonNombreAuDe){
            it->activer(this);
        }
    }
}

/*!
 * \brief active les cartes violettes du joueur correspondant au nbDes
 * \param nbDes
 */
void Joueur::activerCartesViolettes(int nbDes){
    for (auto &it : batiments){
        bool bonNombreAuDe = false;
        for (auto &it2 : it->getCombinaisons())
            if (it2 == nbDes) { bonNombreAuDe = true;}
        if (it->getCouleur()==Couleur::Violet && bonNombreAuDe)
            it->activer(this);
    }
}

/*!
 * \brief ajoute des pièces au joueur
 * \param montant
 */
void Joueur::gagnerPieces(int montant) {
    pieces += montant;
}

/*!
 * \brief Joueur::getNbMonumentsConstruits
 * \return le nombre de batiments construits
 */
int Joueur::getNbMonumentsConstruits(){
    int res = 0;
    for(const auto &m : monuments){
        if(m->getConstruit()){
            res++;
        }
    }
    return res;
}

/*!
 * \brief enlève un batiment de la main d'un joueur
 * \param batiment
 */
void Joueur::enleverBatiment(Batiment* batiment){
    auto it = std::find(batiments.begin(), batiments.end(), batiment);
    if (it != batiments.end()) {
        batiments.erase(it);
    }
}

/*!
 * \brief Joueur::to_string
 * \return un string représentant le joueur
 */
std::string Joueur::to_string(){
    return pseudo + "(" + std::to_string(pieces) + "pièces)";
}

/*!
 * \brief Joueur::getMonuments
 * \return les monuments
 */
vector<Monument*> Joueur::getMonuments() {
    /*vector<Monument*> res;
    for(auto &m : monuments){
        Monument* m_ptr = &m;
        res.push_back(m_ptr);
    }
    return res;*/
    return monuments;
}

/*!
 * \brief destructeur joueur
 */
Joueur::~Joueur(){
    /*for (auto i : monuments)
       delete i;*/
}
