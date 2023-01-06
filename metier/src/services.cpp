#include <string>
#include <QtCore>
#include <algorithm>
#include "../headers/services.h"
#include "../headers/enums.h"
#include "../headers/Batiment.h"
#include "../headers/CarteRouge.h"
#include "../headers/CarteBleue.h"
#include "../headers/CarteVerte.h"
#include "../headers/CarteViolette.h"



vector<int> Service::getCombinaisons(QList<QVariant> combi) {
    std::vector<int> combis;
    for (auto it = combi.begin(); it != combi.end() ; ++it){
        combis.push_back(it->toInt());
    }
    return combis;
}

TypeBatiment Service::determineType(std::string s) {
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

// fonction qui charge une carte Violette
CarteViolette* Service::chargerCarteViolette(QJsonObject objCarte) {
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

// fonction qui charge une carte Rouge
CarteRouge* Service::chargerCarteRouge(QJsonObject objCarte) {
    QJsonObject activation = objCarte.value("activation").toObject();
    CarteRouge* carte = new CarteRouge(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type").toString().toStdString()),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
        Couleur::Rouge,                        // couleur
        activation.value("nbMonuToActivate").toInt() // effet
    );
    return carte;
}

// fonction qui charge une carte Bleue
CarteBleue* Service::chargerCarteBleue(QJsonObject objCarte) {
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
CarteVerte* Service::chargerCarteVerte(QJsonObject objCarte) {
    QJsonObject activation = objCarte.value("activation").toObject();
    CarteVerte* carte = new CarteVerte(
        objCarte.value("id").toInt(),               // id
        objCarte.value("nom").toString().toStdString(),           // nom
        determineType(objCarte.value("type").toString().toStdString()),      // type
        objCarte.value("prix").toInt(),             // prix

        activation.value("gain").toInt(),             // gain
        getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
        Couleur::Vert,                              // couleur
        determineType(activation.value("effectType").toString().toStdString()) // type d'effet
    );
    return carte;
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

Extensions Service::determineExtension(std::string s) {
    return    s == "base"   ?   Extensions::base
            : s == "marina" ?   Extensions::marina
            : Extensions::deluxe;
    // retourne base si s == "base", marina si s == "marina", deluxe sinon
}

// oui j'aime bien les ternaires, mais c'est pas obligatoire

//vector<int> getCombinaisons(QList<QVariant> combi);





vector<Batiment*> Service::chargerCartes(vector<Batiment*> cartes, QJsonObject lstCartes, map<Extensions, bool> extensions, Couleur couleur) {
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

vector<Batiment*> Service::chargerFichier(map<Extensions, bool> extensions) {
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




