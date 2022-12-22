#include "jeu.h"
#include "ui_jeu.h"

Jeu::Jeu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Jeu)
{
    ui->setupUi(this);
}

Jeu::~Jeu()
{
    delete ui;
}

void Jeu::on_actionQuitter_2_triggered()
{
    this->close();
}

