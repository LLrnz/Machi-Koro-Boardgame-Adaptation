#pragma once
#include <string>
#include <QtCore>
#include <algorithm>
#include "../headers/enums.h"
#include "../headers/Batiment.h"
#include "headers/Cartes/CarteBleue.h"
#include "headers/Cartes/CarteRouge.h"
#include "headers/Cartes/CarteVerte.h"
#include "headers/Cartes/CarteViolette.h"

vector<Batiment*> chargerCartes(vector<Batiment*> cartes, QJsonObject lstCartes, map<Extensions, bool> extensions, Couleur couleur);
Extensions determineExtension(std::string s);
TypeBatiment determineType(std::string s);
CarteRouge* chargerCarteRouge(QJsonObject objCarte);
CarteBleue* chargerCarteBleue(QJsonObject objCarte);
CarteVerte* chargerCarteVerte(QJsonObject objCarte);
CarteViolette* chargerCarteViolette(QJsonObject objCarte);

TypeBatiment determineType(std::string s) {
    return    s == "ble"        ?   TypeBatiment::ble 
            : s == "vache"      ?   TypeBatiment::vache 
            : s == "ecrou"      ?   TypeBatiment::ecrou 
            : s == "fruit"      ?   TypeBatiment::fruit 
            : s == "magasin"    ?   TypeBatiment::magasin 
            : s == "usine"      ?   TypeBatiment::usine 
            : s == "restaurant" ?   TypeBatiment::restaurant 
            : TypeBatiment::special;
    //  retourne ble si s == "ble", vache si s == "vache", 
    //  ecrou si s == "ecrou", fruit si s == "fruit", 
    //  magasin si s == "magasin", usine si s == "usine", 
    //  restaurant si s == "restaurant", special sinon
}

/*Source determineSource(std::string s) {
    Source source;
    if (s == "tous_les_joueurs") {
        source = Source::tous_les_joueurs;
    }
    else {
        source = Source::choix_joueur;
    }
    return source;
}*/

Extensions determineExtension(std::string s) {
    return    s == "base"   ?   Extensions::base 
            : s == "marina" ?   Extensions::marina 
            : Extensions::deluxe;
    // retourne base si s == "base", marina si s == "marina", deluxe sinon
}

// oui j'aime bien les ternaires, mais c'est pas obligatoire

vector<int> getCombinaisons(QList<QVariant> combi);

vector<int> getCombinaisons(QList<QVariant> combi) {
    std::vector<int> combis;
    for (auto it = combi.begin(); it != combi.end() ; ++it){
        combis.push_back(it->toInt());
    }
    return combis;
}

vector<Batiment*> chargerFichier(map<Extensions, bool> extensions) {
    vector<Batiment*> cartes;
    QByteArray fichier;
    QFile file(":/cartes/cartes.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Impossible d'accéder au fichier" << std::endl;
    }
    fichier = file.readAll();
    file.close();
    QJsonDocument   fichierCarte = QJsonDocument::fromJson(fichier);
    QJsonObject     objFichierCarte = fichierCarte.object();
    QJsonValue      data = objFichierCarte.value(QString("cartes"));
    QJsonObject     item = data.toObject();
    
    cartes = chargerCartes(cartes, item.value("rouge").toObject(), extensions, Couleur::Rouge);
    cartes = chargerCartes(cartes, item.value("bleue").toObject(), extensions, Couleur::Bleu);
    cartes = chargerCartes(cartes, item.value("verte").toObject(), extensions, Couleur::Vert);
    cartes = chargerCartes(cartes, item.value("violette").toObject(), extensions, Couleur::Violet);
    return cartes;
}

vector<Batiment*> chargerCartes(vector<Batiment*> cartes, QJsonObject lstCartes, map<Extensions, bool> extensions, Couleur couleur) {
    for(const QString& key : lstCartes.keys()) {
        QJsonObject objCarte = lstCartes.value(key).toObject();

        std::vector<Extensions> extensionsCarte;
        for (auto extension : objCarte.value("extension").toArray()) {
            Extensions ex = determineExtension(extension.toString().toStdString());
            extensionsCarte.push_back(ex);
        }
        // si dans extensionsCarte il n'y a pas d'extension qui sont true dans extensions, on passe à la carte suivante
        if (std::find_if(extensionsCarte.begin(), extensionsCarte.end(), [&extensions](Extensions e) { return extensions[e]; }) == extensionsCarte.end()) {
            continue;
        }

        // on ajoute la carte à la liste des cartes
        if (couleur == Couleur::Rouge) {
            for (int i = 0; i < objCarte.value("quantite").toInt(); i++){
                cartes.push_back(chargerCarteRouge(objCarte));
            }
        }
        else if (couleur == Couleur::Bleu) {
            for (int i = 0; i < objCarte.value("quantite").toInt(); i++){
                cartes.push_back(chargerCarteBleue(objCarte));
            }        }
        else if (couleur == Couleur::Vert) {
            for (int i = 0; i < objCarte.value("quantite").toInt(); i++){
                cartes.push_back(chargerCarteVerte(objCarte));
            }        }
        else {
            for (int i = 0; i < objCarte.value("quantite").toInt(); i++){
                cartes.push_back(chargerCarteViolette(objCarte));
            }        }
    }
    return cartes;
}

// fonction qui charge une carte Rouge
CarteRouge* chargerCarteRouge(QJsonObject objCarte) {
    QJsonObject activation = objCarte.value("activation").toObject();
    CarteRouge* carte = new CarteRouge(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type").toString().toStdString()),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
        Couleur::Rouge                        // couleur
        //activation.value("nbMonuToActivate").toInt() // effet
    );
    return carte;
}

// fonction qui charge une carte Bleue
CarteBleue* chargerCarteBleue(QJsonObject objCarte) {
    QJsonObject activation = objCarte.value("activation").toObject();
    CarteBleue* carte = new CarteBleue(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type").toString().toStdString()),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
        Couleur::Bleu                        // couleur
    );
    return carte;
}

// fonction qui charge une carte Verte
CarteVerte* chargerCarteVerte(QJsonObject objCarte) {
    QJsonObject activation = objCarte.value("activation").toObject();
    CarteVerte* carte = new CarteVerte(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type").toString().toStdString()),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
        Couleur::Vert                              // couleur
        //determineType(activation.value("effectType").toString().toStdString()) // type d'effet
    );
    return carte;
}

// fonction qui charge une carte Violette
CarteViolette* chargerCarteViolette(QJsonObject objCarte) {
    QJsonObject activation = objCarte.value("activation").toObject();
    CarteViolette* carte = new CarteViolette(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type").toString().toStdString()),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
        Couleur::Violet                        // couleur
    );
    return carte;
}
