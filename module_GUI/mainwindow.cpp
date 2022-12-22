#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialognouvellepartie.h"
#include "jeu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//À l'aide j'arrive pas à le supprimer
void MainWindow::on_pushButton_3_pressed()
{
}

void MainWindow::on_pb_nouvellePartie_pressed()
{
    DialogNouvellePartie* np = new DialogNouvellePartie();

    np->exec();
    delete np;
    this->close();
    Jeu* j = new Jeu();
    j->show();
}


void MainWindow::on_pbCharger_pressed()
{

}


void MainWindow::on_pbQuitter_pressed()
{
    this->close();
}

