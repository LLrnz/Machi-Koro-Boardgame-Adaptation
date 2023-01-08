#include "../../gui/headers/dialognouvellepartie.h"
#include "ui_dialognouvellepartie.h"
#include "../../gui/headers/dialognouveaujoueur.h"
#include <iostream>
#include "../../metier/headers/Jeu.h"


DialogNouvellePartie::DialogNouvellePartie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNouvellePartie)
{
    ui->setupUi(this);
    ui->lwExtensions->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->lwExtensions->addItem("Marina");
    ui->lwExtensions->addItem("Deluxe");
    extensions.emplace(Extensions::base, true);
}

DialogNouvellePartie::~DialogNouvellePartie()
{
    delete ui;
}

void DialogNouvellePartie::on_pbNouveauJoueur_clicked()
{
    // on lance une boite de dialogue pour créer un nouveau joueur
    DialogNouveauJoueur* nj = new DialogNouveauJoueur();
    nj->exec();
    // on récupère les données saisies
    string pseudo = nj->getPseudo();
    TypeJoueur type = nj->getHuman() ? TypeJoueur::humain : TypeJoueur::IA;
    // on supprime le formulaire
    delete nj;
    // on ajoute les infos du joueur dans la map
    joueurs[pseudo] = type;
    // et on met à jour l'affichage de lwJoueur
    ui->lwJoueurs->addItem(QString::fromStdString(pseudo));
}


void DialogNouvellePartie::on_buttonBox_accepted()
{
    // on récupère les extensions selectionnées
    QList<QListWidgetItem*> selectedItems = ui->lwExtensions->selectedItems();
    for (QListWidgetItem *item : selectedItems){
        string extensionName = item->text().toStdString();
        if (extensionName == "Marina")
            extensions.emplace(Extensions::marina, true);
        else if (extensionName == "Deluxe")
            extensions.emplace(Extensions::deluxe, true);
    }
    // on génère une nouvelle partie
    Jeu::getJeu().genererPartie(joueurs, extensions);
}

