#pragma once
#include <string>
#include <QtCore>
#include "../headers/enums.h"

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

void chargerFichier(vector<Carte*> cartes, map<Extensions, bool> extensions) {
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
    
    chargerCartes(cartes, item.value("rouge").toObject(), extensions, Couleur::Rouge);
    chargerCartes(cartes, item.value("bleue").toObject(), extensions, Couleur::Bleu);
    chargerCartes(cartes, item.value("verte").toObject(), extensions, Couleur::Vert);
    chargerCartes(cartes, item.value("violette").toObject(), extensions, Couleur::Violet);
}

void chargerCartes(vector<Carte*> cartes, QJsonObject lstCartes, map<Extensions, bool> extensions, Couleur couleur) {
    for(const QString& key : lstCartes.keys()) {
        QJsonObject objCarte = lstCartes.value(key).toObject();

        std::vector<Extensions> extensionsCarte;
        for (const QString& extension : objCarte.value("extensions").toArray()) {
            extensionsCarte.push_back(determineExtension(extension.toString().toStdString()));
        }
        // si dans extensionsCarte aucunes des exentions ne sont dans extensions, on passe à la carte suivante
        if (std::find_first_of(extensionsCarte.begin(), extensionsCarte.end(), extensions.begin(), extensions.end()) == extensionsCarte.end()) {
            continue;
        }


        // on ajoute la carte à la liste des cartes
        cartes.push_back(couleur == Couleur::Rouge  ?   chargerCarteRouge(objCarte) 
                    : couleur == Couleur::Bleu      ?   chargerCarteBleue(objCarte) 
                    : couleur == Couleur::Vert      ?   chargerCarteVerte(objCarte) 
                    : chargerCarteViolette(objCarte));
    }
}

// fonction qui charge une carte Rouge
CarteRouge* chargerCarteRouge(QJsonObject objCarte) {
    QJsonValue activation = value.value("activation");
    CarteRouge* carte new CarteRouge(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type")),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        activation.value("combinaisons").toArray().toVariantList().toStdVector(), // combinaisons
        Couleur::Rouge,                        // couleur
        activation.value("nbMonuToActivate").toInt() // effet
    )
    return carte;
}

// fonction qui charge une carte Bleue
CarteBleue* chargerCarteBleue(QJsonObject objCarte) {
    QJsonValue activation = value.value("activation");
    CarteBleue* carte new CarteBleue(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type")),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        activation.value("combinaisons").toArray().toVariantList().toStdVector(), // combinaisons
        Couleur::Bleu,                        // couleur
    )
    return carte;
}

// fonction qui charge une carte Verte
CarteVerte* chargerCarteVerte(QJsonObject objCarte) {
    QJsonValue activation = value.value("activation");
    CarteVerte* carte new CarteVerte(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type")),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        activation.value("combinaisons").toArray().toVariantList().toStdVector(), // combinaisons
        Couleur::Vert,                              // couleur
        determineType(activation.value("effectType")) // type d'effet
    )
    return carte;
}

// fonction qui charge une carte Violette
CarteViolette* chargerCarteViolette(QJsonObject objCarte) {
    QJsonValue activation = value.value("activation");
    CarteViolette* carte new CarteViolette(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type")),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        activation.value("combinaisons").toArray().toVariantList().toStdVector(), // combinaisons
        Couleur::Violet,                        // couleur
    )
    return carte;
}