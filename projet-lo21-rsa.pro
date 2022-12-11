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
        src/Controleur.cpp \
        src/CarteBleue.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

HEADERS += \
    headers/Batiment.h \
    headers/Carte.h \
    headers/CarteBleue.h \
    headers/CarteRouge.h \
    headers/CarteVerte.h \
    headers/CarteViolette.h \
    headers/Jeu.h \
    headers/Controleur.h \
    headers/enums.h \
    headers/InterfaceInterminal.h \
    headers/Jeu.h \
    headers/Joueur.h \
    headers/Monument.h \
    headers/marche.h \
    headers/enums.h
