#ifndef PARAMETRESPARTIE_H
#define PARAMETRESPARTIE_H

#include <QDialog>

namespace Ui {
class ParametresPartie;
}

class ParametresPartie : public QDialog
{
    Q_OBJECT

public:
    explicit ParametresPartie(QWidget *parent = nullptr);
    ~ParametresPartie();

private slots:
    void on_pbCommencer_pressed();

    void on_pbNouveauJoueur_pressed();

private:
    Ui::ParametresPartie *ui;
};

#endif // PARAMETRESPARTIE_H
