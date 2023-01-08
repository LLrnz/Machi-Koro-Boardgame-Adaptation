#ifndef SERVICES_H
#define SERVICES_H

#include "qjsonobject.h"
#endif // SERVICES_H

#include "../headers/enums.h"
#include "../headers/Batiment.h"
#include "../headers/CarteRouge.h"
#include "../headers/CarteBleue.h"
#include "../headers/CarteVerte.h"
#include "../headers/CarteViolette.h"

class Service{



    static vector<int> getCombinaisons(QList<QVariant> combi);
    static Extensions determineExtension(std::string s);
    static TypeBatiment determineType(std::string s);
    static CarteRouge* chargerCarteRouge(QJsonObject objCarte);
    static CarteBleue* chargerCarteBleue(QJsonObject objCarte);
    static CarteVerte* chargerCarteVerte(QJsonObject objCarte);
    static CarteViolette* chargerCarteViolette(QJsonObject objCarte);


public :
    static vector<Batiment*> chargerCartes(vector<Batiment*> cartes, QJsonObject lstCartes, map<Extensions, bool> extensions, Couleur couleur);
    static vector<Batiment*> chargerFichier(map<Extensions, bool> extensions);
};
