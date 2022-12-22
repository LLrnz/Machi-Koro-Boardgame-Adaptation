#ifndef JEU_H
#define JEU_H

#include <QMainWindow>

namespace Ui {
class Jeu;
}

class Jeu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Jeu(QWidget *parent = nullptr);
    ~Jeu();

private slots:
    void on_actionQuitter_2_triggered();

private:
    Ui::Jeu *ui;
};

#endif // JEU_H
