#include "../../gui/headers/dialognouveaujoueur.h"
#include "ui_dialognouveaujoueur.h"
#include "../../metier/headers/Joueur.h"

DialogNouveauJoueur::DialogNouveauJoueur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNouveauJoueur)
{
    ui->setupUi(this);
}

DialogNouveauJoueur::~DialogNouveauJoueur()
{
    delete ui;
}

/**
 * @brief Valide le nom du joueur
 */
void DialogNouveauJoueur::on_buttonBox_accepted()
{
    // Récupération des valeurs du formulaire :
    isHuman = ui->isHuman->isChecked();
    pseudo = ui->pseudo->text().toStdString();



}

