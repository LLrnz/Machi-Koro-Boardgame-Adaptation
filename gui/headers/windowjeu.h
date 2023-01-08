#ifndef WINDOWJEU_H
#define WINDOWJEU_H

#include "qlistwidget.h"
#include <QMainWindow>
#include <QLabel>

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
private slots:
    void on_actionQuitter_2_triggered();


    void on_listMarche_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);


    void on_listMarche_itemClicked(QListWidgetItem *item);

    void on_pbAcheter_clicked();

private:
    Ui::WindowJeu *ui;
};

#endif // JEU_H
