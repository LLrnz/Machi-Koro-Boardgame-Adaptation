#include "../../gui/headers/windowjeu.h"
#include "ui_windowjeu.h"
#include "../../metier/headers/Jeu.h"
#include "../../metier/headers/CarteRouge.h"
#include <QErrorMessage>
#include "../../metier/headers/enums.h"
#include <QVBoxLayout>


WindowJeu::WindowJeu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowJeu)
{
    ui->setupUi(this);
    ui->pb1de->setEnabled(false);
    ui->pb2de->setEnabled(false);
    ui->pbRelancer->setEnabled(false);
    ui->pbAcheter->setEnabled(false);
    ui->pbFin->setEnabled(false);

    //TEST
    joueurs = std::vector<Joueur*>();
    batiments = std::vector<Batiment*>();

}
void WindowJeu::init(){
    this->show();


    //JEU DE TEST
    this->actif = new Joueur("Eudes", TypeJoueur::humain);
    actif->ajouterBatiment(new CarteRouge(12,"Café",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));

    joueurs.push_back(actif);
    joueurs.push_back(new Joueur("Gilles", TypeJoueur::humain));
    joueurs.push_back(new Joueur("Chantale", TypeJoueur::humain));

    batiments.push_back(new CarteRouge(12,"resto1",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));
    batiments.push_back(new CarteRouge(12,"resto2",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));
    batiments.push_back(new CarteRouge(12,"resto3",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));

    this->rafraichirMarcher();
    this->rafraichirJoueurs();
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





    for(auto &b : batiments){
    //FIN DU JEU DE TEST


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

void WindowJeu::rafraichirJoueurs(){
    ui->listeAdversaires->clear();




    for(auto &j : joueurs){
    //FIN DU JEU DE TEST


    //for(auto &j : Jeu::getJeu().getJoueurs()){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(j->getPseudo()));
        // Association de l'adresse du batiment aux données de l'élément
        item->setData(Qt::UserRole, QVariant::fromValue(j));
        ui->listeAdversaires->addItem(item);
        ui->tJoueurActif->setText(QString::fromStdString(actif->getPseudo()));
    }
}





void WindowJeu::on_listMarche_itemClicked(QListWidgetItem *item)
{
    Batiment* b = item->data(Qt::UserRole).value<Batiment*>();
    this->mettreAJourCarteSelec(b);

}


void WindowJeu::on_pbAcheter_clicked()
{
    if(ui->listMarche->currentItem() != nullptr){
        Batiment* b = ui->listMarche->currentItem()->data(Qt::UserRole).value<Batiment*>();
        Jeu::getJeu().getMarche()->acheter(b);

    }else{
        QErrorMessage *error = new QErrorMessage();
        error->showMessage("Aucune carte sélectionnée.");
    }
}


void WindowJeu::on_listeAdversaires_itemClicked(QListWidgetItem *item)
{
    Joueur* j = item->data(Qt::UserRole).value<Joueur*>();

    ui->tJoueur->setText(QString::fromStdString(j->getPseudo()));
    ui->tPiece->setText(QString::number(j->getPieces()));

    ui->listBatiment->clear();
    for(auto &b : j->getConstructions()){

        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(b->getNom()));
        // Association de l'adresse du batiment aux données de l'élément
        item->setData(Qt::UserRole, QVariant::fromValue(b));
        ui->listBatiment->addItem(item);

    }

    ui->listMonuments->clear();
    for(auto &m : j->getMonuments()){

        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(m->getNom()));
        // Association de l'adresse du batiment aux données de l'élément
        item->setData(Qt::UserRole, QVariant::fromValue(m));
        if(m->getConstruit()){
            const QColor jaune = QColor(220, 200, 0);
            item->setBackground(jaune);
        }else{
            const QColor gris = QColor(220, 230, 230);
            item->setBackground(gris);
        }
        ui->listMonuments->addItem(item);

    }

    qApp->processEvents();
}


void WindowJeu::on_listBatiment_itemClicked(QListWidgetItem *item)
{
    Batiment* b = item->data(Qt::UserRole).value<Batiment*>();
    this->mettreAJourCarteSelec(b);
}



void WindowJeu::mettreAJourCarteSelec(Batiment *b){
    this->mettreAJourCarteCarteSelec(b);
    ui->tGain->setText(QString::number(b->getGain()));

    QString combinaisons = "";
    for(auto &c : b->getCombinaisons()){
        combinaisons.append(QString::number(c));
        combinaisons.append(" ");
    }

    ui->tCombinaisons->setText(combinaisons);

    QString style = "background-color : " + b->getStyle() + "; color : rgb(0,0,0)";
    ui->tnomCarte->setStyleSheet(style);
    qApp->processEvents();
}

void WindowJeu::mettreAJourCarteSelec(Monument *b){
    this->mettreAJourCarteCarteSelec(b);
    ui->tGain->setText("N/A");

    ui->tCombinaisons->setText("N/A");

    QString style = "background-color : (220, 200, 0); color : rgb(0,0,0)";
    ui->tnomCarte->setStyleSheet(style);
    qApp->processEvents();
}

void WindowJeu::mettreAJourCarteCarteSelec(Carte *c){
    ui->tnomCarte->setText(QString::fromStdString(c->getNom()));

    ui->tPrix->setText(QString::number(c->getPrix()));

    ui->tEffet->setText(QString::fromStdString(c->to_string()));
}


void WindowJeu::on_listMonuments_itemClicked(QListWidgetItem *item)
{
    Monument* m = item->data(Qt::UserRole).value<Monument*>();
    this->mettreAJourCarteSelec(m);
}

