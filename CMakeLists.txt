cmake_minimum_required(VERSION 3.5)

project(rsa-gui-v2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp

        gui/src/mainwindow.cpp gui/headers/mainwindow.h gui/src/mainwindow.ui
        gui/headers/windowjeu.h gui/src/windowjeu.cpp gui/src/windowjeu.ui
        gui/headers/dialognouveaujoueur.h gui/src/dialognouveaujoueur.cpp gui/src/dialognouveaujoueur.ui
        gui/headers/dialognouvellepartie.h gui/src/dialognouvellepartie.cpp gui/src/dialognouvellepartie.ui


        metier/src/Batiment.cpp metier/headers/Batiment.h
        metier/src/Carte.cpp metier/headers/Carte.h
        metier/src/cartesbleues.cpp metier/headers/cartesbleues.h
        metier/src/cartesrouges.cpp metier/headers/cartesrouges.h
        metier/src/cartesvertes.cpp metier/headers/cartesvertes.h
        metier/src/cartesviolettes.cpp metier/headers/cartesviolettes.h
        metier/src/Controleur.cpp metier/headers/Controleur.h
        metier/src/InterfaceTerminal.cpp
        metier/src/Jeu.cpp metier/headers/Jeu.h
        metier/src/Joueur.cpp metier/headers/Joueur.h
        metier/src/Marche.cpp metier/headers/marche.h
        metier/src/Monument.cpp metier/headers/Monument.h metier/headers/CartesMonuments.h
        metier/src/services.cpp
        metier/headers/services.h
        metier/headers/enums.h
        metier/headers/InterfaceTerminal.h
        cartes.json
        metier/headers/IA.h
        metier/src/IA.cpp
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(rsa-gui-v2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET rsa-gui-v2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(rsa-gui-v2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(rsa-gui-v2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(rsa-gui-v2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(rsa-gui-v2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS rsa-gui-v2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(rsa-gui-v2)
endif()

add_definitions("-DPATH_TO_JSON=\"${CMAKE_SOURCE_DIR}/cartes.json\" ")
