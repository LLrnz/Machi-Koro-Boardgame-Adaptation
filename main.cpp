
#include "metier/headers/Controleur.h"



int main(int argc, char *argv[])
{

    int a = Controleur::getControleur()->menuPrincipal(argc, argv);

    return a;
}
