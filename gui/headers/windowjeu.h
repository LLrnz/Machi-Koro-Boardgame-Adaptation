#ifndef WINDOWJEU_H
#define WINDOWJEU_H

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

private slots:
    void on_actionQuitter_2_triggered();


private:
    Ui::WindowJeu *ui;
};

#endif // JEU_H
