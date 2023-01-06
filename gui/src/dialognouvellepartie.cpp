#include "../../gui/headers/dialognouvellepartie.h"
#include "ui_dialognouvellepartie.h"


DialogNouvellePartie::DialogNouvellePartie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNouvellePartie)
{
    ui->setupUi(this);
}

DialogNouvellePartie::~DialogNouvellePartie()
{
    delete ui;
}
