#include "../../gui/headers/windowjeu.h"
#include "ui_windowjeu.h"



WindowJeu::WindowJeu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowJeu)
{
    ui->setupUi(this);
}

WindowJeu::~WindowJeu()
{
    delete ui;
}

void WindowJeu::on_actionQuitter_2_triggered()
{
    this->close();
}

