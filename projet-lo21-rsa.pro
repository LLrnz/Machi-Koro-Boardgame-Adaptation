QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/Cartes/BarASushi.cpp \
    src/Cartes/CarteBleue.cpp \
    src/Cartes/CarteRouge.cpp \
    src/Cartes/CarteVerte.cpp \
    src/Cartes/CarteViolette.cpp \
    src/Cartes/CentreAffaires.cpp \
    src/Cartes/CentreImpot.cpp \
    src/Cartes/ChaineTV.cpp \
    src/Cartes/Chalutier.cpp \
    src/Cartes/ClubPrive.cpp \
    src/Cartes/EntrepriseDemenage.cpp \
    src/Cartes/EntrepriseTravauxPub.cpp \
    src/Cartes/Epicerie.cpp \
    src/Cartes/Fleuriste.cpp \
    src/Cartes/MaisonEdition.cpp \
    src/Cartes/MonsterSoda.cpp \
    src/Cartes/PetitBateauDePeche.cpp \
    src/Cartes/RougeNbBat.cpp \
    src/Cartes/Stade.cpp \
    src/Cartes/VerteEffet.cpp \
        src\Batiment.cpp \
        src\Carte.cpp \
        src\cartesbleues.cpp \
        src\cartesrouges.cpp \
        src\cartesvertes.cpp \
        src\cartesviolettes.cpp \
        src\Controleur.cpp \
        src\InterfaceTerminal.cpp \
        src\Jeu.cpp \
        src\Joueur.cpp \
        src\Marche.cpp \
        src\Monument.cpp \
        src\services.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    README.md \
    cartes.json

HEADERS += \
    headers/Cartes/BarASushi.h \
    headers/Cartes/CarteBleue.h \
    headers/Cartes/CarteRouge.h \
    headers/Cartes/CarteVerte.h \
    headers/Cartes/CarteViolette.h \
    headers/Cartes/CentreAffaires.h \
    headers/Cartes/CentreImpot.h \
    headers/Cartes/ChaineTV.h \
    headers/Cartes/Chalutier.h \
    headers/Cartes/ClubPrive.h \
    headers/Cartes/EntrepriseDemenage.h \
    headers/Cartes/EntrepriseTravauxPub.h \
    headers/Cartes/Epicerie.h \
    headers/Cartes/Fleuriste.h \
    headers/Cartes/MaisonEdition.h \
    headers/Cartes/MonsterSoda.h \
    headers/Cartes/PetitBateauDePeche.h \
    headers/Cartes/RougeNbBat.h \
    headers/Cartes/Stade.h \
    headers/Cartes/VerteEffet.h \
    headers\Batiment.h \
    headers\Carte.h \
    headers\cartesbleues.h \
    headers\CartesMonuments.h \
    headers\cartesrouges.h \
    headers\cartesvertes.h \
    headers\cartesviolettes.h \
    headers\Controleur.h \
    headers\enums.h \
    headers\InterfaceTerminal.h \
    headers\Jeu.h \
    headers\Joueur.h \
    headers\marche.h \
    headers\Monument.h \


RESOURCES += \
    ressources.qrc
