#ifndef NOUVEAUJOUEUR_H
#define NOUVEAUJOUEUR_H

#include <QMainWindow>

namespace Ui {
class NouveauJoueur;
}

class NouveauJoueur : public QMainWindow
{
    Q_OBJECT

public:
    explicit NouveauJoueur(QWidget *parent = nullptr);
    ~NouveauJoueur();

private:
    Ui::NouveauJoueur *ui;
};

#endif // NOUVEAUJOUEUR_H
