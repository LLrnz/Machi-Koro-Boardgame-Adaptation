#include "headers/Jeu.h"
#include "headers/CarteBleue.h"
#include "headers/CarteRouge.h"
#include "headers/CarteVerte.h"
#include "headers/CarteViolette.h"
#include <QtCore>
#include <iostream>

TypeBatiment determineType(std::string s) {
    TypeBatiment type;
    if (s == "ble") {
        type = TypeBatiment::ble;
    }
    else if (s == "vache") {
        type = TypeBatiment::vache;
    }
    else if (s == "ecrou") {
        type = TypeBatiment::ecrou;
    }
    else if (s == "fruit") {
        type = TypeBatiment::fruit;
    }
    else if (s == "magasin") {
        type = TypeBatiment::magasin;
    }
    else if (s == "usine") {
        type = TypeBatiment::usine;
    }
    else if (s == "restaurant") {
        type = TypeBatiment::restaurant;
    }
    else {
        type = TypeBatiment::special;
    }
    return type;
}

Source determineSource(std::string s) {
    Source source;
    if (s == "tous_les_joueurs") {
        source = Source::tous_les_joueurs;
    }
    else {
        source = Source::choix_joueur;
    }
    return source;
}

void Jeu::initialiserCartes() {
    QByteArray val;
    QFile file(":/cartes/cartes.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Impossible d'accéder au fichier" << std::endl;
    }
    val = file.readAll();
    file.close();
    QJsonDocument fichierCarte = QJsonDocument::fromJson(val);
    QJsonObject objFichierCarte = fichierCarte.object();
    QJsonValue data = objFichierCarte.value(QString("cartes"));
    QJsonObject item = data.toObject();


    int id = 0;
    QJsonObject lstCarteBleue = item.value(QString("bleu")).toObject();
    for(const QString& key: lstCarteBleue.keys()) {
        QJsonObject value = lstCarteBleue.value(key).toObject();

        std::string nom = value.value("nom").toString().toStdString();
        int prix = value.value("prix").toInt();
        int quantite = value.value("quantite").toInt();
        std::string otype = value.value("type").toString().toStdString();
        QJsonValue activation = value.value("activation");

        int gain = activation.toObject().value("gain").toInt();

        std::vector<int> combinaisons;
        for (QJsonValueRef combi : activation.toObject().value("nb").toArray()) {
            combinaisons.push_back(combi.toInt());
        }
        TypeBatiment type = determineType(otype);


        for (int i = 0; i < quantite; i++) {
            cartesEnJeu.push_back(new CarteBleue(id, nom, type, prix, gain, combinaisons));
            id += 1;
        }

    }

    // Parcours de la liste des cartes vertes
    // On récupère les informations de chaque carte
    // On les stocke dans un vecteur de cartes
    QJsonObject lstCarteVerte = item.value(QString("verte")).toObject();
    for(const QString& key: lstCarteVerte.keys()) {
        QJsonObject value = lstCarteVerte.value(key).toObject();

        std::string nom = value.value("nom").toString().toStdString();
        int prix = value.value("prix").toInt();
        int quantite = value.value("quantite").toInt();
        std::string otype = value.value("type").toString().toStdString();
        QJsonValue activation = value.value("activation");

        int gain = activation.toObject().value("gain").toInt();

        std::vector<int> combinaisons;
        for (QJsonValueRef combi : activation.toObject().value("nb").toArray()) {
            combinaisons.push_back(combi.toInt());
        }
        TypeBatiment type = determineType(otype);

        for (int i = 0; i < quantite; i++) {
            cartesEnJeu.push_back(new CarteVerte(id, nom, type, prix, gain, combinaisons));
            id += 1;
        }
    }

    // Parcours de la liste des cartes rouges
    // On récupère les informations de chaque carte
    // On les stocke dans un vecteur de cartes
    QJsonObject lstCarteRouge = item.value(QString("rouge")).toObject();
    for(const QString& key: lstCarteRouge.keys()) {
        QJsonObject value = lstCarteRouge.value(key).toObject();

        std::string nom = value.value("nom").toString().toStdString();
        int prix = value.value("prix").toInt();
        int quantite = value.value("quantite").toInt();
        std::string otype = value.value("type").toString().toStdString();
        QJsonValue activation = value.value("activation");

        int gain = activation.toObject().value("gain").toInt();

        std::vector<int> combinaisons;
        for (QJsonValueRef combi : activation.toObject().value("nb").toArray()) {
            combinaisons.push_back(combi.toInt());
        }
        TypeBatiment type = determineType(otype);

        for (int i = 0; i < quantite; i++) {
            cartesEnJeu.push_back(new CarteRouge(id, nom, type, prix, gain, combinaisons));
            id += 1;
        }
    }

    // Parcours de la liste des cartes violettes
    // On récupère les informations de chaque carte
    // On les stocke dans un vecteur de cartes
    // Les cartes violettes ont un attribut en plus nommé "source"
    QJsonObject lstCarteViolette = item.value(QString("violet")).toObject();
    for(const QString& key: lstCarteViolette.keys()) {
        QJsonObject value = lstCarteViolette.value(key).toObject();

        std::string nom = value.value("nom").toString().toStdString();
        int prix = value.value("prix").toInt();
        int quantite = value.value("quantite").toInt();
        std::string otype = value.value("type").toString().toStdString();
        QJsonValue activation = value.value("activation");

        int gain = activation.toObject().value("gain").toInt();

        std::vector<int> combinaisons;
        for (QJsonValueRef combi : activation.toObject().value("nb").toArray()) {
            combinaisons.push_back(combi.toInt());
        }
        TypeBatiment type = determineType(otype);

        std::string source = activation.toObject().value("source").toString().toStdString();
        Source typeSource = determineSource(source);

        for (int i = 0; i < quantite; i++) {
            cartesEnJeu.push_back(new CarteViolette(id, nom, type, prix, gain, combinaisons, typeSource));
            id += 1;
        }
    }
}

Jeu::Jeu() {
    initialiserCartes();
}

Jeu::~Jeu() {
    for (Carte* c : cartesEnJeu) {
        delete c;
    }
}

void Jeu::afficherCartes() {
    for (Carte* c : cartesEnJeu) {
        std::cout << c->getNom() << std::endl;
    }
}
