#ifndef DIALOGNOUVELLEPARTIE_H
#define DIALOGNOUVELLEPARTIE_H

#include "../../metier/headers/enums.h "

#include <QDialog>

namespace Ui {
class DialogNouvellePartie;
}

class DialogNouvellePartie : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNouvellePartie(QWidget *parent = nullptr);
    ~DialogNouvellePartie();

private slots:
    void on_pbNouveauJoueur_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogNouvellePartie *ui;
    map<std::string, TypeJoueur> joueurs;
    map<Extensions, bool> extensions;
};

#endif // DIALOGNOUVELLEPARTIE_H
