QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
        metier\src\Batiment.cpp \
        metier\src\Carte.cpp \
        metier\src\cartesbleues.cpp \
        metier\src\cartesrouges.cpp \
        metier\src\cartesvertes.cpp \
        metier\src\cartesviolettes.cpp \
        metier\src\Controleur.cpp \
        metier\src\InterfaceTerminal.cpp \
        metier\src\Jeu.cpp \
        metier\src\Joueur.cpp \
        metier\src\Marche.cpp \
        metier\src\Monument.cpp \
        metier\src\services.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    README.md \
    cartes.json

HEADERS += \
    metier\headers\Batiment.h \
    metier\headers\Carte.h \
    metier\headers\cartesbleues.h \
    metier\headers\CartesMonuments.h \
    metier\headers\cartesrouges.h \
    metier\headers\cartesvertes.h \
    metier\headers\cartesviolettes.h \
    metier\headers\Controleur.h \
    metier\headers\enums.h \
    metier\headers\InterfaceTerminal.h \
    metier\headers\Jeu.h \
    metier\headers\Joueur.h \
    metier\headers\marche.h \
    metier\headers\Monument.h \


RESOURCES += \
    ressources.qrc
