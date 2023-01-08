#pragma once
#include "../headers/Monument.h"

class Port : public Monument{
    public :
    Port(std::string n,int p):Monument(n, p){};

    std::string to_string() const{
        return "Permet d'ajouter 1 ou 2 à un jet supérieur à 10.";
    }
    ~Port()= default;
};

class Gare : public Monument{
    public :
    Gare(std::string n,int p):Monument(n, p){};
    std::string to_string() const{
        return "Permet de lancer 1 ou 2 dés.";
    }
    ~Gare() = default;
};

class ParcDattraction : public Monument{
    public :
    ParcDattraction(std::string n,int p):Monument(n, p){};
    std::string to_string() const{
        return "Permet de rejouer si vous faîtes un double au dés.";
    }
    ~ParcDattraction() = default;
};

class Aeroport : public Monument{
    public :
    Aeroport(std::string n,int p):Monument(n, p){};
    std::string to_string() const{
        return "Gagnez 10 pièces si vous ne construisez rien ce tour-ci.";
    }
    ~Aeroport() = default;
};

class CentreCommercial : public Monument{
    public :
    CentreCommercial(std::string n,int p):Monument(n, p){};
    std::string to_string() const{
        return "Gagner le double de la production de chaque établissement du type tartine ou café.";
    }
    ~CentreCommercial() = default;
};

class TourRadio : public Monument{
    public :
    TourRadio(std::string n,int p):Monument(n, p){};
    std::string to_string() const{
        return "["+ Monument::getNom() + "] " + std::to_string(Monument::getPrix()) + " : Permet de relancer les dés une fois par tour.";
    }
    ~TourRadio() = default;
};


