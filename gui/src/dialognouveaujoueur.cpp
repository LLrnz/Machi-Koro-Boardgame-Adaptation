#include "../../gui/headers/dialognouveaujoueur.h"
#include "ui_dialognouveaujoueur.h"

DialogNouveauJoueur::DialogNouveauJoueur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNouveauJoueur)
{
    ui->setupUi(this);
}

DialogNouveauJoueur::~DialogNouveauJoueur()
{
    delete ui;
}
