#ifndef NOUVELLEPARTIE_H
#define NOUVELLEPARTIE_H

#include <QMainWindow>

namespace Ui {
class NouvellePartie;
}

class NouvellePartie : public QMainWindow
{
    Q_OBJECT

public:
    explicit NouvellePartie(QWidget *parent = nullptr);
    ~NouvellePartie();

private:
    Ui::NouvellePartie *ui;
};

#endif // NOUVELLEPARTIE_H
