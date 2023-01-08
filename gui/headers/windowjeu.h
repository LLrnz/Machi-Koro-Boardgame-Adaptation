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
    Joueur* joueurAffiche;
    Carte* carteAffiche;

    //JEU DE TEST
    Joueur* actif;
    std::vector<Joueur*> joueurs;
    std::vector<Batiment*> batiments;

public:
    explicit WindowJeu(QWidget *parent = nullptr);
    ~WindowJeu();
    QLabel* getConsole();
    void rafraichirMarcher();
    void rafraichirJoueurs();
    void init();




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
    void mettreAJourJoueurSelec(Joueur* j);
    void on_listMonuments_itemClicked(QListWidgetItem *item);

    void on_pb1de_clicked();
    void debutDeTour();
    void on_pb2de_clicked();
    void proposerRelancer(int nbdes, int score);
    void activerCartes(int nb);

    void on_listJoueurActif_itemClicked(QListWidgetItem *item);

    void on_pbPasser_clicked();
    void finDeTour();

private:
    Ui::WindowJeu *ui;
};

#endif // JEU_H
