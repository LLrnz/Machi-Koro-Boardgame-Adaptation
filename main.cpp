#include <QtCore>
#include <iostream>

//#include "./headers/Jeu.h"
#include "headers/Carte.h"
#include "headers/enums.h"

int main() {

    std::vector<Carte> cartes;

    QByteArray val;
    QFile file;
    file.setFileName("c:/test/cartes.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Impossible d'accéder au fichier" << std::endl;
    }
    val = file.readAll();
    file.close();
    QJsonDocument fichierCarte = QJsonDocument::fromJson(val);
    QJsonObject objFichierCarte = fichierCarte.object();
    QJsonValue data = objFichierCarte.value(QString("cartes"));
    QJsonObject item = data.toObject();
    QJsonObject lstCarteBleue = item.value(QString("bleu")).toObject();

    int id = 0;
    for(const QString& key: lstCarteBleue.keys()) {
        QJsonObject value = lstCarteBleue.value(key).toObject();

        std::string nom = value.value("nom").toString().toStdString();
        int prix = value.value("prix").toInt();
        int quantite = value.value("quantite").toInt();
        std::string type = value.value("type").toString().toStdString();
        QJsonValue activation = value.value("activation");

        int gain = activation.toObject().value("gain").toInt();

        std::vector<int> combinaisons;
        for (QJsonValueRef combi : activation.toObject().value("nb").toArray()) {
            combinaisons.push_back(combi.toInt());
        }

        std::cout << "Nom : " << nom << " Prix : " << prix << " Quantité : "
                  << quantite << " Type : " << type << " Gain : " << gain << " Combinaisons : [";
        for (int i : combinaisons){
            std::cout << i << " ";
        }
        std::cout << "]" << std::endl;

        id++;
    }

    // qWarning() << lstCarteBleue.keys();

    return 0;
}
