QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src\cartesbleues.cpp \
    src\cartesrouges.cpp \
    src\cartesvertes.cpp \
    src\cartesviolettes.cpp \
        main.cpp \
    src/Monument.cpp \
        src\Batiment.cpp \
        src\Carte.cpp \
        src\CarteBleue.cpp \
        src\CarteRouge.cpp \
        src\CarteVerte.cpp \
        src\CarteViolette.cpp \
        src\Controleur.cpp \
        src\InterfaceTerminal.cpp \
        src\Jeu.cpp \
        src\Joueur.cpp \
        src\Marche.cpp \
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
    headers\cartesbleues.h \
    headers\cartesrouges.h \
    headers\cartesvertes.h \
    headers\cartesviolettes.h \
    headers/CartesMonuments.h \
    headers/Monument.h \
    headers\Batiment.h \
    headers\Carte.h \
    headers\CarteBleue.h \
    headers\CarteRouge.h \
    headers\CarteVerte.h \
    headers\CarteViolette.h \
    headers\Controleur.h \
    headers\enums.h \
    headers\InterfaceTerminal.h \
    headers\Jeu.h \
    headers\Joueur.h \
    headers\Marche.h \
    headers\Monument.h \


RESOURCES += \
    ressources.qrc
