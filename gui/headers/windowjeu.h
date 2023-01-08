#ifndef WINDOWJEU_H
#define WINDOWJEU_H

#include "qlistwidget.h"
#include <QMainWindow>
#include <QLabel>
#include "../../metier/headers/Monument.h"
#include "../../metier/headers/Batiment.h"
#include "../../metier/headers/Carte.h"

namespace Ui {
class WindowJeu;
}

class WindowJeu : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowJeu(QWidget *parent = nullptr);
    ~WindowJeu();
    QLabel* getConsole();
    void rafraichirMarcher();
    void rafraichirJoueurs();
    void init();

    //JEU DE TEST
    Joueur* actif;
    std::vector<Joueur*> joueurs;
    std::vector<Batiment*> batiments;

private slots:
    void on_actionQuitter_2_triggered();


    void on_listMarche_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);


    void on_listMarche_itemClicked(QListWidgetItem *item);

    void on_pbAcheter_clicked();

    void on_listeAdversaires_itemClicked(QListWidgetItem *item);

    void on_listBatiment_itemClicked(QListWidgetItem *item);
    void mettreAJourCarteSelec(Monument* c);
    void mettreAJourCarteSelec(Batiment* c);
    void mettreAJourCarteCarteSelec(Carte* c);

    void on_listMonuments_itemClicked(QListWidgetItem *item);

private:
    Ui::WindowJeu *ui;
};

#endif // JEU_H
