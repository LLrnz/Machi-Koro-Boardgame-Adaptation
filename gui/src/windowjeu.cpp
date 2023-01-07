#include "../../gui/headers/windowjeu.h"
#include "ui_windowjeu.h"
#include "../../metier/headers/Jeu.h"
#include "../../metier/headers/CarteRouge.h"


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
        batiments.push_back(new CarteRouge(12,"resto1",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));
        batiments.push_back(new CarteRouge(12,"resto2",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));
        batiments.push_back(new CarteRouge(12,"resto3",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));



    for(auto &b : batiments){
    //FIN DU JEU DE TEST
    //for(auto &b : Jeu::getJeu().getMarche()->getCarteDispAchat()){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(b->to_string()));
        // Association de l'adresse du batiment aux données de l'élément
        item->setData(Qt::UserRole, QVariant::fromValue(b));
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

