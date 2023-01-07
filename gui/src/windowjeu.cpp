#include "../../gui/headers/windowjeu.h"
#include "ui_windowjeu.h"
#include "../../metier/headers/Jeu.h"



WindowJeu::WindowJeu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowJeu)
{
    ui->setupUi(this);


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



