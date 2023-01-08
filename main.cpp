
#include "gui/headers/mainwindow.h"
#include "metier/headers/Controleur.h"
#include "qapplication.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.show();

    return a.exec();
}


// ANCIEN MAIN
/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.show();
    return a.exec();
}
*/


// AFFICHAGE LISTE BATIMENTS CLIQUABLE (cf affichage grille plus bas)
/* :
#include "metier/headers/Batiment.h"
#include "metier/headers/CarteRouge.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>

int main(int argc, char *argv[]){

    // Création d'une liste de bâtiments (pour tester l'affichage)
    std::vector<Batiment*> batiments;
    batiments.push_back(new CarteRouge(12,"resto1",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));
    batiments.push_back(new CarteRouge(12,"resto2",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));
    batiments.push_back(new CarteRouge(12,"resto3",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));

    QApplication app(argc, argv);

    // Création d'une liste
    QListWidget listWidget;

    // Création d'une zone de texte
    QLabel affichageAdresseCarte;

    // Ajout des éléments à la liste
    for (Batiment *batiment : batiments) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(batiment->to_string()));
        // Association de l'adresse du batiment aux données de l'élément
        item->setData(Qt::UserRole, QVariant::fromValue(batiment));
        listWidget.addItem(item);
    }

    // Connexion du signal itemClicked de la liste au slot de l'étiquette
    QObject::connect(&listWidget, &QListWidget::itemClicked, &app, [&](QListWidgetItem *item){
        Batiment* batiment = item->data(Qt::UserRole).value<Batiment*>();
        affichageAdresseCarte.setText("adresse de la carte selectionnée : "+QString::number(reinterpret_cast<quint64>(batiment)));
    });

    QVBoxLayout layout;
    layout.addWidget(&listWidget);
    layout.addWidget(&affichageAdresseCarte);

    QWidget window;
    window.setGeometry(0, 0, 800, 400);
    window.setLayout(&layout);

    window.show();

    return app.exec();
};
*/



// AFFICHAGE BATIMENTS CLIQUABLE SOUS FORME DE GRILLE
/*
#include "metier/headers/Batiment.h"
#include "metier/headers/CarteRouge.h"
#include "metier/headers/CarteBleue.h"
#include "metier/headers/CarteVerte.h"
#include "metier/headers/CarteViolette.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QLabel>
#include <QVariant>
#include <QColor>
#include <QBrush>

int main(int argc, char *argv[]){

    // Création d'une liste de bâtiments (pour tester l'affichage)
    std::vector<Batiment*> batiments;
    batiments.push_back(new CarteRouge(12,"Restaurant",TypeBatiment::ble, 12, 4, {1}, Couleur::Rouge, 2));
    batiments.push_back(new CarteBleue(12,"Batiment bleu",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Bleu));
    batiments.push_back(new CarteViolette(12,"Carte Violette",TypeBatiment::ble, 12, 4, {6}, Couleur::Violet));
    batiments.push_back(new CarteRouge(7,"Batiment Sans Nom",TypeBatiment::ble, 12, 4, {1,2,3}, Couleur::Rouge, 2));
    batiments.push_back(new CarteVerte(12,"Batiment Vert",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Vert, TypeBatiment::ecrou));
    batiments.push_back(new CarteRouge(12,"Truc Rouge",TypeBatiment::ble, 12, 4, {6}, Couleur::Rouge, 2));
    batiments.push_back(new CarteRouge(12,"restaurant 5 étoiles",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));
    batiments.push_back(new CarteVerte(12,"Autre Batiment Vert",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Vert, TypeBatiment::ecrou));
    batiments.push_back(new CarteBleue(12,"Autre Batiment Bleu",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Bleu));

    QApplication app(argc, argv);

    // Création d'une liste
    QListWidget listWidget;
    listWidget.setViewMode(QListView::IconMode);

    // Création d'une zone de texte
    QLabel affichageAdresseCarte;

    // Ajout des éléments à la liste
    for (Batiment *batiment : batiments) {
        QListWidgetItem *item = new QListWidgetItem();

        // création du texte contenu dans les cases :
        string str = batiment->getNom() + "\n";
        for(const auto &i : batiment->getCombinaisons()){str += std::to_string(i) + ",";}
        str.pop_back(); // pour enlever la dernière virgule (après la liste des combinaisons)
        str+= "🎲  +" + std::to_string(batiment->getGain()) + "🪙";
        item->setText(QString::fromStdString(str));

        // Association de l'adresse du batiment aux données de l'élément
        item->setData(Qt::UserRole, QVariant::fromValue(batiment));

        // Configuration de la taille et de la couleur de la case
        item->setSizeHint(QSize(120, 80));
        switch(batiment->getCouleur()){
        case Couleur::Bleu:
            item->setBackground(QBrush(QColor(130, 228, 244)));
            break;
        case Couleur::Vert:
            item->setBackground(QBrush(QColor(190, 247, 159)));
            break;
        case Couleur::Rouge:
            item->setBackground(QBrush(QColor(255, 159, 159)));
            break;
        case Couleur::Violet:
            item->setBackground(QBrush(QColor(228, 159, 255)));
            break;
        }

        listWidget.setSpacing(10);

        listWidget.addItem(item);
    }

    // Connexion du signal itemClicked de la liste au slot de l'étiquette
    QObject::connect(&listWidget, &QListWidget::itemClicked, &app, [&](QListWidgetItem *item){
        Batiment* batiment = item->data(Qt::UserRole).value<Batiment*>();
        affichageAdresseCarte.setText("adresse de la carte selectionnée : "+QString::number(reinterpret_cast<quint64>(batiment)));
    });

    QVBoxLayout layout;
    layout.addWidget(&listWidget);
    layout.addWidget(&affichageAdresseCarte);

    QWidget window;
    window.setGeometry(0, 0, 800, 400);
    window.setLayout(&layout);

    window.show();

    return app.exec();
};
*/
