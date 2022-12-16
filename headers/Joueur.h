#pragma once
#include <iostream>
#include <vector>
#include "../headers/enums.h"
#include "../headers/Batiment.h"
#include "../headers/Monument.h"
using namespace std;

class Joueur
{
    TypeJoueur type;
    string pseudo;
    int pieces;
    bool rejoueTour = false;
    vector<Batiment*> batiments;
    vector<Monument> monuments;

public:
    Joueur(std::string psdo, TypeJoueur typ);
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
    std::vector<Monument> getMonuments()const{return monuments;}; // OK GET BATIMENT tout doux
    std::vector<Batiment*> getConstructions() const {return batiments;};
    int getPieces() const {return pieces;};
    string getPseudo() const {return pseudo;};
    void ajouterBatiment(Batiment * batiment){batiments.push_back(batiment);};
    void enleverBatimentParIndice(int i){batiments.erase(batiments.begin()+i);};
};
