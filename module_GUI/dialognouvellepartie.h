#ifndef DIALOGNOUVELLEPARTIE_H
#define DIALOGNOUVELLEPARTIE_H

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

private:
    Ui::DialogNouvellePartie *ui;
};

#endif // DIALOGNOUVELLEPARTIE_H
