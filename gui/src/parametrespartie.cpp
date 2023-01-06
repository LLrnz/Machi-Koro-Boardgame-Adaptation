#include "parametrespartie.h"
#include "dialognouveaujoueur.h"
#include "ui_parametrespartie.h"

ParametresPartie::ParametresPartie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParametresPartie)
{
    ui->setupUi(this);
}

ParametresPartie::~ParametresPartie()
{
    delete ui;
}

//void ParametresPartie::on_pbCommencer_pressed()
//{
//    this->close();
//}


void ParametresPartie::on_pbNouveauJoueur_pressed()
{
    DialogNouveauJoueur* nj = new DialogNouveauJoueur();
    nj->exec();
    delete nj;
}

