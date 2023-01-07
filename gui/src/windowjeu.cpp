#include "../../gui/headers/windowjeu.h"
#include "ui_windowjeu.h"
#include "../../metier/headers/Jeu.h"



WindowJeu::WindowJeu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowJeu)
{
    ui->setupUi(this);
    ui->pb1de->setEnabled(false);
    ui->pb2de->setEnabled(false);
    ui->pbRelancer->setEnabled(false);
    ui->pbAcheter->setEnabled(false);

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

}

void WindowJeu::on_listMarche_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

}

