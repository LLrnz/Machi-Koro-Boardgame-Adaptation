#include "../../gui/headers/windowjeu.h"
#include "ui_windowjeu.h"
#include "../../metier/headers/Jeu.h"
#include "../../metier/headers/CarteRouge.h"
#include "../../metier/headers/CarteBleue.h"
#include "../../metier/headers/CarteVerte.h"
#include "../../metier/headers/CarteViolette.h"
#include "../../metier/headers/Batiment.h"


WindowJeu::WindowJeu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowJeu)
{
    ui->setupUi(this);
    ui->pb1de->setEnabled(false);
    ui->pb2de->setEnabled(false);
    ui->pbRelancer->setEnabled(false);
    ui->pbAcheter->setEnabled(false);

    QVBoxLayout layout;
    layout.addWidget(ui->listMarche);

    ui->listMarche->setViewMode(QListView::IconMode);

    this->rafraichirMarcher();



}
QLabel* WindowJeu::getConsole()
{return this->ui->texteConsole;}

WindowJeu::~WindowJeu()
{
    delete ui;

}

void WindowJeu::on_actionQuitter_2_triggered()
{
    this->close();
}


void WindowJeu::rafraichirMarcher(){

    //JEU DE TEST
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
    //FIN DU JEU DE TEST


    for(auto &b : batiments){
    //for(auto &b : Jeu::getJeu().getMarche()->getCarteDispAchat()){
        QListWidgetItem *item = new QListWidgetItem();

        // création du texte contenu dans les cases :
        string str = b->getNom() + "\n";
        for(const auto &i : b->getCombinaisons()){str += std::to_string(i) + ",";}
        str.pop_back(); // pour enlever la dernière virgule (après la liste des combinaisons)
        str+= "🎲  +" + std::to_string(b->getGain()) + "🪙";
        str+= "\n prix : " + std::to_string(b->getPrix());
        item->setText(QString::fromStdString(str));
        // Association de l'adresse du batiment aux données de l'élément
        item->setData(Qt::UserRole, QVariant::fromValue(b));
        // Configuration de la taille et de la couleur de la case
        item->setSizeHint(QSize(120, 80));
        switch(b->getCouleur()){
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
        ui->listMarche->setSpacing(10);
        ui->listMarche->addItem(item);
    }

}

void WindowJeu::on_listMarche_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{



}





void WindowJeu::on_listMarche_itemClicked(QListWidgetItem *item)
{
    Batiment* b = item->data(Qt::UserRole).value<Batiment*>();

    ui->tnomCarte->setText(QString::fromStdString(b->getNom()));
    ui->tGain->setText(QString::number(b->getGain()));
    ui->tPrix->setText(QString::number(b->getPrix()));
    QString combinaisons = "";
    for(auto &c : b->getCombinaisons()){
        combinaisons.append(QString::number(c));
        combinaisons.append(" ");
    }

    ui->tCombinaisons->setText(combinaisons);
    ui->tEffet->setText(QString::fromStdString(b->to_string()));

    QString style = "background-color : " + b->getStyle() + "; color : rgb(0,0,0)";
    ui->tnomCarte->styleSheet() = style;
    qApp->processEvents();
}

