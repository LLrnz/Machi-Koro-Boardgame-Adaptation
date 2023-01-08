#pragma once
#include <string>
#include <QtCore>
#include <algorithm>
#include "../headers/enums.h"
#include "../headers/Batiment.h"
#include "headers/cartesbleues.h"
#include "headers/cartesrouges.h"
#include "headers/cartesvertes.h"
#include "headers/cartesviolettes.h"

vector<Batiment *> chargerCartes(vector<Batiment *> cartes, QJsonObject lstCartes, map<Extensions, bool> extensions, Couleur couleur);
Extensions determineExtension(std::string s);
TypeBatiment determineType(std::string s);
CarteRouge *chargerCarteRouge(QJsonObject objCarte);
CarteBleue *chargerCarteBleue(QJsonObject objCarte);
CarteVerte *chargerCarteVerte(QJsonObject objCarte);
CarteViolette *chargerCarteViolette(QJsonObject objCarte);

TypeBatiment determineType(std::string s)
{
    return s == "ble"          ? TypeBatiment::ble
           : s == "vache"      ? TypeBatiment::vache
           : s == "ecrou"      ? TypeBatiment::ecrou
           : s == "fruit"      ? TypeBatiment::fruit
           : s == "magasin"    ? TypeBatiment::magasin
           : s == "usine"      ? TypeBatiment::usine
           : s == "restaurant" ? TypeBatiment::restaurant
                               : TypeBatiment::special;
    //  retourne ble si s == "ble", vache si s == "vache",
    //  ecrou si s == "ecrou", fruit si s == "fruit",
    //  magasin si s == "magasin", usine si s == "usine",
    //  restaurant si s == "restaurant", special sinon
}

Extensions determineExtension(std::string s)
{
    return s == "base"     ? Extensions::base
           : s == "marina" ? Extensions::marina
                           : Extensions::deluxe;
    // retourne base si s == "base", marina si s == "marina", deluxe sinon
}

// oui j'aime bien les ternaires

vector<int> getCombinaisons(QList<QVariant> combi);

vector<int> getCombinaisons(QList<QVariant> combi)
{
    std::vector<int> combis;
    for (auto it = combi.begin(); it != combi.end(); ++it)
    {
        combis.push_back(it->toInt());
    }
    return combis;
}

vector<Batiment *> chargerFichier(map<Extensions, bool> extensions)
{
    vector<Batiment *> cartes;
    QByteArray fichier;
    QFile file(":/cartes/cartes.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Impossible d'accéder au fichier" << std::endl;
    }
    fichier = file.readAll();
    file.close();
    QJsonDocument fichierCarte = QJsonDocument::fromJson(fichier);
    QJsonObject objFichierCarte = fichierCarte.object();
    QJsonValue data = objFichierCarte.value(QString("cartes"));
    QJsonObject item = data.toObject();

    cartes = chargerCartes(cartes, item.value("rouge").toObject(), extensions, Couleur::Rouge);
    cartes = chargerCartes(cartes, item.value("bleue").toObject(), extensions, Couleur::Bleu);
    cartes = chargerCartes(cartes, item.value("verte").toObject(), extensions, Couleur::Vert);
    cartes = chargerCartes(cartes, item.value("violette").toObject(), extensions, Couleur::Violet);
    return cartes;
}

vector<Batiment *> chargerCartes(vector<Batiment *> cartes, QJsonObject lstCartes, map<Extensions, bool> extensions, Couleur couleur)
{
    for (const QString &key : lstCartes.keys())
    {
        QJsonObject objCarte = lstCartes.value(key).toObject();

        std::vector<Extensions> extensionsCarte;
        for (auto extension : objCarte.value("extension").toArray())
        {
            Extensions ex = determineExtension(extension.toString().toStdString());
            extensionsCarte.push_back(ex);
        }
        // si dans extensionsCarte il n'y a pas d'extension qui sont true dans extensions, on passe à la carte suivante
        if (std::find_if(extensionsCarte.begin(), extensionsCarte.end(), [&extensions](Extensions e)
                         { return extensions[e]; }) == extensionsCarte.end())
        {
            continue;
        }

        // on ajoute la carte à la liste des cartes
        if (couleur == Couleur::Rouge)
        {
            for (int i = 0; i < objCarte.value("quantite").toInt(); i++)
            {
                cartes.push_back(chargerCarteRouge(objCarte));
            }
        }
        else if (couleur == Couleur::Bleu)
        {
            for (int i = 0; i < objCarte.value("quantite").toInt(); i++)
            {
                cartes.push_back(chargerCarteBleue(objCarte));
            }
        }
        else if (couleur == Couleur::Vert)
        {
            for (int i = 0; i < objCarte.value("quantite").toInt(); i++)
            {
                cartes.push_back(chargerCarteVerte(objCarte));
            }
        }
        else
        {
            for (int i = 0; i < objCarte.value("quantite").toInt(); i++)
            {
                cartes.push_back(chargerCarteViolette(objCarte));
            }
        }
    }
    return cartes;
}

// fonction qui charge une carte Rouge
CarteRouge *chargerCarteRouge(QJsonObject objCarte)
{
    QJsonObject activation = objCarte.value("activation").toObject();

    switch (objCarte.value("id").toInt())
    {
    case 5: // si c'est le bar à sushi
        return new BarASushi(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Rouge,
            objCarte.value("description").toString().toStdString() // description
        );
        break;

    case 6: // si c'est le club privé
        return new ClubPrive(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Rouge,
            objCarte.value("description").toString().toStdString(), // description                                                             // couleur
            activation.value("nbMonuToActivate").toInt()            // effet
        );
        break;

    case 7: // si c'est le resto 5 etoiles
        return new RougeNbBat(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Rouge,
            objCarte.value("description").toString().toStdString(), // description                                                              // couleur
            activation.value("nbBatToActivate").toInt()             // effet
        );
        break;

    default:
        return new CarteRouge(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Rouge,
            objCarte.value("description").toString().toStdString() // description
        );
        break;
    }
}

// fonction qui charge une carte Bleue
CarteBleue *chargerCarteBleue(QJsonObject objCarte)
{
    QJsonObject activation = objCarte.value("activation").toObject();

    switch (objCarte.value("id").toInt())
    {
    case 7: // si c'est le petit bateau de pêche
        return new PetitBateauDePeche(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Bleu,
            objCarte.value("description").toString().toStdString() // description                                                                // effet
        );
        break;

    case 8: // si c'est le chalutier
        return new Chalutier(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Bleu,
            objCarte.value("description").toString().toStdString() // description                                                                // effet
        );
        break;

    default:
        return new CarteBleue(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Bleu,
            objCarte.value("description").toString().toStdString() // description;
        );
        break;
    }
}

// fonction qui charge une carte Verte
CarteVerte *chargerCarteVerte(QJsonObject objCarte)
{
    QJsonObject activation = objCarte.value("activation").toObject();

    switch (objCarte.value("id").toInt())
    {
        {
        case 3: // si c'est une usine de fromage
        case 4: // si c'est le magasin de meuble
        case 5: // si c'est le marché fruit et légume
        case 7: // si c'est la halle de marché
            return new VerteEffet(
                objCarte.value("id").toInt(),                                   // id
                objCarte.value("nom").toString().toStdString(),                 // nom
                determineType(objCarte.value("type").toString().toStdString()), // type
                objCarte.value("prix").toInt(),                                 // prix

                activation.value("gain").toInt(),                                            // gain
                getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
                Couleur::Vert,                                                               // couleur
                objCarte.value("description").toString().toStdString(),                      // description
                determineType(activation.value("effectType").toString().toStdString())       // type d'effet
            );
            break;

        case 6: // si c'est un fleuriste
            return new Fleuriste(
                objCarte.value("id").toInt(),                                   // id
                objCarte.value("nom").toString().toStdString(),                 // nom
                determineType(objCarte.value("type").toString().toStdString()), // type
                objCarte.value("prix").toInt(),                                 // prix

                activation.value("gain").toInt(),                                            // gain
                getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
                Couleur::Vert,                                                               // couleur
                objCarte.value("description").toString().toStdString());
            break;
        default:
            return new CarteVerte(
                objCarte.value("id").toInt(),                                   // id
                objCarte.value("nom").toString().toStdString(),                 // nom
                determineType(objCarte.value("type").toString().toStdString()), // type
                objCarte.value("prix").toInt(),                                 // prix

                activation.value("gain").toInt(),                                            // gain
                getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
                Couleur::Vert,
                objCarte.value("description").toString().toStdString() // description
            );
            break;
        }
    }
}
// fonction qui charge une carte Violette
CarteViolette *chargerCarteViolette(QJsonObject objCarte)
{
    QJsonObject activation = objCarte.value("activation").toObject();

    switch (objCarte.value("id").toInt())
    {
    case 1: // si c'est le stade
        return new Stade(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Violet,                                                             // couleur
            objCarte.value("description").toString().toStdString()                       // description
        );
        break;

    case 2: // si c'est la chaine TV
        return new ChaineTV(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Violet,                                                             // couleur
            objCarte.value("description").toString().toStdString()                       // description
        );
        break;

    case 3: // si c'est le centre des affaires
        return new CentreAffaires(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Violet,                                                             // couleur
            objCarte.value("description").toString().toStdString()                       // description
        );
        break;

    case 4: // si c'est la masion d'édition
        return new MaisonEdition(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Violet,                                                             // couleur
            objCarte.value("description").toString().toStdString()                       // description
        );
        break;

    default: // si c'est le centre des impots
        return new CentreImpot(
            objCarte.value("id").toInt(),                                   // id
            objCarte.value("nom").toString().toStdString(),                 // nom
            determineType(objCarte.value("type").toString().toStdString()), // type
            objCarte.value("prix").toInt(),                                 // prix

            activation.value("gain").toInt(),                                            // gain
            getCombinaisons(activation.value("combinaisons").toArray().toVariantList()), // combinaisons
            Couleur::Violet,                                                             // couleur
            objCarte.value("description").toString().toStdString()                       // description
        );
        break;
    }
}
