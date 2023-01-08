#ifndef DIALOGNOUVEAUJOUEUR_H
#define DIALOGNOUVEAUJOUEUR_H

#include <string>
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
    std::string getPseudo() const { return pseudo; }
    bool getHuman() const { return isHuman; }

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogNouveauJoueur *ui;
    std::string pseudo;
    bool isHuman;
};

#endif // DIALOGNOUVEAUJOUEUR_H
