#pragma once

#include <iostream>
#include <vector>

#include "enums.h"
#include "headers/Monument.h"

class Batiment;
class Monument;

class Joueur
{
    TypeJoueur type;
    std::string pseudo;
    int pieces;
    bool rejoueTour = false;
    std::vector<Batiment*> constructions;
    std::vector<Monument> monuments;

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
    std::vector<Monument> getMonuments()const{return monuments;};
    std::vector<Batiment*> getConstructions() const {return constructions;};
    int getPieces() const {return pieces;};
    string getPseudo() const {return pseudo;};
    void ajouterBatiment(Batiment * batiment){constructions.push_back(batiment);};
    void enleverBatimentParIndice(int i){constructions.erase(constructions.begin()+i);};
};
