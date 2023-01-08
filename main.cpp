
#include "gui/headers/mainwindow.h"
#include "metier/headers/Controleur.h"
#include "qapplication.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.show();

    return a.exec();
}
