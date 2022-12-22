#ifndef DIALOGNOUVEAUJOUEUR_H
#define DIALOGNOUVEAUJOUEUR_H

#include <QDialog>

namespace Ui {
class DialogNouveauJoueur;
}

class DialogNouveauJoueur : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNouveauJoueur(QWidget *parent = nullptr);
    ~DialogNouveauJoueur();

private:
    Ui::DialogNouveauJoueur *ui;
};

#endif // DIALOGNOUVEAUJOUEUR_H
