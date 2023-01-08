#pragma once
#include <iostream>
#include <vector>

#include "../headers/Monument.h"
#include "../headers/Batiment.h"


using namespace std;

class Joueur
{
    TypeJoueur type;
    string pseudo;
    int pieces;
    bool rejoueTour = false;
    vector<Batiment*> batiments;
    vector<Monument*> monuments;

public:
    Joueur(std::string psdo, TypeJoueur typ);
    ~Joueur();
    bool hasGare() const;
    bool hasCentreCommercial() const;
    bool hasParcAttractions() const;
    bool hasTourRadio() const;
    bool hasPort() const;
    bool hasAeroport()const;
    void extracted(int &nbDes, std::vector<Batiment *>::iterator &it, bool &bonNombreAuDe);
    void activerCartesBleues(int nbDes);
    void activerCartesVertes(int nbDes);
    void activerCartesRouges(int nbDes);
    void activerCartesViolettes(int nbDes);
    void gagnerPieces(int montant);
    int perdrePieces(int montant);
    void setRejoueTour(bool b){rejoueTour = b;};
    std::vector<Monument*> getMonuments(); // OK GET BATIMENT tout doux
    std::vector<Batiment*> getConstructions() const {return batiments;};
    int getPieces() const {return pieces;};
    string getPseudo() const {return pseudo;};
    void ajouterBatiment(Batiment * batiment){batiments.push_back(batiment);};
    void enleverBatiment(Batiment * batiment);
    int getNbMonumentsConstruits();
    std::string to_string();

    bool operator!=(Joueur& j){
        bool res = false;
        if (j.pseudo != this->pseudo){
            res = true;
        }else if(j.batiments != this->batiments){
            res = true;
        }else if(j.pieces != this->pieces){
            res = true;
        }
        return res;
    }

    bool isIA(){
        bool res = false;
        if (this->type == TypeJoueur::IA){
            res = true;
        }
            return res;
    }


};
