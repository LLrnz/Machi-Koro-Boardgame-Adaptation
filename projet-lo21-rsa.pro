QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/Batiment.cpp \
        src/Carte.cpp \
        src/CarteBleue.cpp \
        src/Jeu.cpp \
        src/CarteRouge.cpp \
        src/CarteVerte.cpp \
        src/CarteViolette.cpp \
        src/Controleur.cpp \
        src/Joueur.cpp \
    src/services.cpp \
        src\InterfaceTerminal.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    README.md \
    cartes.json

HEADERS += \
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
