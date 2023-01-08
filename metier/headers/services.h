#ifndef SERVICES_H
#define SERVICES_H

#include "qjsonobject.h"
#endif // SERVICES_H

#include "../../metier/headers/enums.h"
#include "../../metier/headers/Batiment.h"
#include "../../metier/headers/cartesrouges.h"
#include "../../metier/headers/Cartesbleues.h"
#include "../../metier/headers/cartesvertes.h"
#include "../../metier/headers/cartesviolettes.h"

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
