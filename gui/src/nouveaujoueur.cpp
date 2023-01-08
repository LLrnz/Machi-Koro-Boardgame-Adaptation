#include "nouveaujoueur.h"
#include "ui_nouveaujoueur.h"

NouveauJoueur::NouveauJoueur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NouveauJoueur)
{
    ui->setupUi(this);
}

NouveauJoueur::~NouveauJoueur()
{
    delete ui;
}
