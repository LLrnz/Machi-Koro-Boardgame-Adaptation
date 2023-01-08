#include "../../gui/headers/windowjeu.h"
#include "ui_windowjeu.h"
#include "../../metier/headers/Jeu.h"
#include "../../metier/headers/cartesrouges.h"
#include <QErrorMessage>
#include "../../metier/headers/enums.h"
#include <QVBoxLayout>
#include "../../metier/headers/Controleur.h"
#include <vector>
#include <algorithm>
#include "../../metier/headers/Batiment.h"
#include "../../metier/headers/Joueur.h"
#include <QMessageBox>

WindowJeu::WindowJeu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowJeu)
{
    ui->setupUi(this);
    ui->pb1de->setEnabled(false);
    ui->pb2de->setEnabled(false);

    ui->pbAcheter->setEnabled(false);
    ui->pbPasser->setEnabled(false);

}
void WindowJeu::init(){
    this->show();


//    //JEU DE TEST
//    this->actif = new Joueur("Eudes", TypeJoueur::humain);
//    actif->ajouterBatiment(new CarteRouge(12,"Café",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));

//    //joueurs.push_back(actif);
//    joueurs.push_back(new Joueur("Gilles", TypeJoueur::humain));
//    joueurs.push_back(new Joueur("Chantale", TypeJoueur::humain));

//    batiments.push_back(new CarteRouge(12,"resto1",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));
//    batiments.push_back(new CarteRouge(12,"resto2",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));
//    batiments.push_back(new CarteRouge(12,"resto3",TypeBatiment::ble, 12, 4, {1,2}, Couleur::Rouge, 2));


    this->debutDeTour();
    ui->listMarche->setViewMode(QListView::IconMode);
    ui->listBatiment->setViewMode(QListView::IconMode);

}

QTextBrowser* WindowJeu::getConsole()
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



    ui->listMarche->clear();

    for(auto &b : Jeu::getJeu().getMarche()->getCarteDispAchat()){
    //FIN DU JEU DE TEST


    //for(auto &b : Jeu::getJeu().getMarche()->getCarteDispAchat()){
        QListWidgetItem *item = new QListWidgetItem();
        // création du texte contenu dans les cases :
        string str = b->getNom() + "\n";
        for(const auto &i : b->getCombinaisons()){str += std::to_string(i) + ",";}
        str.pop_back(); // pour enlever la dernière virgule (après la liste des combinaisons)
        str+= "🎲  + Gain : " + std::to_string(b->getGain()) + "\n" + std::to_string(b->getPrix()) + "🪙";
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
    ui->listJoueurActif->clear();

    //ajout joueur actif
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(QString::fromStdString(Jeu::getJeu().getJoueurActif()->getPseudo()));
    // Association de l'adresse du batiment aux données de l'élément
    item->setData(Qt::UserRole, QVariant::fromValue(Jeu::getJeu().getJoueurActif()));
    ui->listJoueurActif->addItem(item);
    ui->tJoueurActif->setText(QString::fromStdString(Jeu::getJeu().getJoueurActif()->getPseudo()));

    //ajout adversaires
    for(auto &j : Jeu::getJeu().getJoueursSansActifPtr()){
    //FIN DU JEU DE TEST


    //for(auto &j : Jeu::getJeu().getJoueurs()){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(j->getPseudo()));
        // Association de l'adresse du batiment aux données de l'élément
        item->setData(Qt::UserRole, QVariant::fromValue(j));
        ui->listeAdversaires->addItem(item);

    }
    //qApp->processEvents();
}





void WindowJeu::on_listMarche_itemClicked(QListWidgetItem *item)
{
    Batiment* b = item->data(Qt::UserRole).value<Batiment*>();
    this->mettreAJourCarteSelec(b);
    if(Jeu::getJeu().getDeLance()){
        ui->pbAcheter->setEnabled(true);
    }
}


void WindowJeu::on_pbAcheter_clicked()
{
    if(carteAffiche != nullptr){


        if(Jeu::getJeu().achat(carteAffiche)){
            Controleur::getControleur()->afficher("Achat effectué avec succès.\n");
            this->finDeTour();
        }else{
            QErrorMessage *error = new QErrorMessage();
            error->showMessage("Vous n'avez pas assez de pièces.");
        }



    }else if(!Jeu::getJeu().getDeLance()){
        QErrorMessage *error = new QErrorMessage();
        error->showMessage("Il faut jetter les dés avant d'acheter une carte.");
    }else{
        QErrorMessage *error = new QErrorMessage();
        error->showMessage("Aucune carte sélectionnée.");
    }
    this->rafraichirMarcher();
}


void WindowJeu::on_listeAdversaires_itemClicked(QListWidgetItem *item)
{
    Joueur* j = item->data(Qt::UserRole).value<Joueur*>();
    this->mettreAJourJoueurSelec(j);
    ui->pbAcheter->setEnabled(false);

}


void WindowJeu::on_listBatiment_itemClicked(QListWidgetItem *item)
{
    Batiment* b = item->data(Qt::UserRole).value<Batiment*>();
    this->mettreAJourCarteSelec(b);
    ui->pbAcheter->setEnabled(false);

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
    ui->tEffet->setText(QString::fromStdString(b->getDescription()));
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
    this->carteAffiche = c;
}


void WindowJeu::on_listMonuments_itemClicked(QListWidgetItem *item)
{
    Monument* m = item->data(Qt::UserRole).value<Monument*>();
    this->mettreAJourCarteSelec(m);

    if(this->joueurAffiche == Jeu::getJeu().getJoueurActif() && Jeu::getJeu().getDeLance()){

        ui->pbAcheter->setEnabled(true);
    }else{
        ui->pbAcheter->setEnabled(false);
    }

}

void WindowJeu::mettreAJourJoueurSelec(Joueur* j){
    this->joueurAffiche = j;
    ui->tJoueur->setText(QString::fromStdString(j->getPseudo()));
    ui->tPiece->setText(QString::number(j->getPieces()));

    ui->listBatiment->clear();
    for(auto &b : j->getConstructions()){

        QListWidgetItem *item = new QListWidgetItem();
        string str = b->getNom() + "\n";
        for(const auto &i : b->getCombinaisons()){str += std::to_string(i) + ",";}
        str.pop_back(); // pour enlever la dernière virgule (après la liste des combinaisons)
        str+= "🎲  +" + std::to_string(b->getGain()) + "🪙";
        item->setText(QString::fromStdString(str));
        // Association de l'adresse du batiment aux données de l'élément
        item->setData(Qt::UserRole, QVariant::fromValue(b));
        item->setSizeHint(QSize(100, 40));
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

        ui->listBatiment->setSpacing(7);
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

void WindowJeu::debutDeTour(){
    this->rafraichirMarcher();
    this->rafraichirJoueurs();
    Jeu::getJeu().setDeLance(false);
    Controleur::getControleur()->afficher("\nC'est à " + Jeu::getJeu().getJoueurActif()->getPseudo() + " de jouer !\n");
    if(Jeu::getJeu().getJoueurActif()->hasGare()){
        ui->pb2de->setEnabled(true);
    }
    ui->pb1de->setEnabled(true);
    this->mettreAJourJoueurSelec(Jeu::getJeu().getJoueurActif());
    Jeu::getJeu().setDesRelances(false);

    ui->pbAcheter->setEnabled(false);
    ui->pbPasser->setEnabled(false);

}

void WindowJeu::on_pb1de_clicked()
{
    int nb = Jeu::getJeu().lancer1de();
    if (Jeu::getJeu().getJoueurActif()->hasTourRadio()){
        this->proposerRelancer(1, nb);
    }
    ui->pb1de->setEnabled(false);
    ui->pbPasser->setEnabled(true);
    this->activerCartes(nb);
    Jeu::getJeu().setDeLance(true);
    this->rafraichirJoueurs();

}


void WindowJeu::on_pb2de_clicked()
{
    int nb = Jeu::getJeu().lancer2des();

    //Avec le port, le joueur peut moduler son jet
    if ((nb >= 10) && (Jeu::getJeu().getJoueurActif()->hasPort())){

        ///Ouvrir boite de dialogue;
//        Controleur::getControleur()->afficher("Le résultat est superieur à 10 ! \n");
//        Controleur::getControleur()->afficher("Le résultat du jet est ");
//        Controleur::getControleur()->afficher(to_string(resultatJet));
//        Controleur::getControleur()->afficher("Vous pouvez ajouter de 0 à 2 à votre jet. Combien ajouter ? \n");

        //int rep = Controleur::getControleur()->lire_int(0, 2);
        nb += 0;
    }
    if(!Jeu::getJeu().getDesRelances()){
        this->proposerRelancer(2, nb);
    }
    ui->pb1de->setEnabled(false);
    ui->pb2de->setEnabled(false);
    ui->pbPasser->setEnabled(true);
    this->activerCartes(nb);
    Jeu::getJeu().setDeLance(true);
    this->rafraichirJoueurs();
}

void WindowJeu::proposerRelancer(int nbdes, int score){
    if(!Jeu::getJeu().getDesRelances()){
        ///Ouvrir boite de dialogue relancer
        //Controleur::getControleur()->afficher("0 : Ne pas relancer les dés \n");
        //Controleur::getControleur()->afficher("1 : Relancer les dés \n");
        //int reponse = Controleur::getControleur()->lire_int(0, 1);
        //if (reponse)
        //	resultatJet = jetDes();
        Jeu::getJeu().setDesRelances(true);
    }

}

void WindowJeu::activerCartes(int nb){
    Jeu::getJeu().activerCartes(nb);
    ui->pbAcheter->setEnabled(false);
    ui->pbPasser->setEnabled(true);
    this->mettreAJourJoueurSelec(joueurAffiche);
}

void WindowJeu::on_listJoueurActif_itemClicked(QListWidgetItem *item)
{
    Joueur* j = item->data(Qt::UserRole).value<Joueur*>();
    this->mettreAJourJoueurSelec(j);
    ui->pbAcheter->setEnabled(false);


}

void WindowJeu::afficherJoueur(QListWidgetItem* item){
    Joueur* j = item->data(Qt::UserRole).value<Joueur*>();
    this->mettreAJourJoueurSelec(j);
    ui->pbAcheter->setEnabled(false);
}





void WindowJeu::on_listMarche_currentItemChanged(QListWidgetItem*, QListWidgetItem*){
    //rien
}

void WindowJeu::on_pbPasser_clicked()
{
    Jeu::getJeu().toucherRSA();
    this->finDeTour();
}

void WindowJeu::finDeTour(){
    ui->pbAcheter->setEnabled(false);
    ui->pbPasser->setEnabled(false);
    bool fin = Jeu::getJeu().finDeTour();
    Controleur::getControleur()->afficher("Fin de tour.\n");

    if(fin){
        QMessageBox msgBox;
        msgBox.setText("Le joueur " + QString::fromStdString(Jeu::getJeu().getJoueurActif()->getPseudo()) + "a gagné !");
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Close);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Close:
              delete(this);
              break;
          default:
              // should never be reached
              break;
        }
    }else{
        this->debutDeTour();
    }
}

