#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "nouvellepartie.h"

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
    NouvellePartie* np = new NouvellePartie();
    //this->hide();
    np->show();
    delete np;
}


void MainWindow::on_pbCharger_pressed()
{

}


void MainWindow::on_pbQuitter_pressed()
{
    this->close();
}

