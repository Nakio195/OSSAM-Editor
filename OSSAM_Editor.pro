#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T18:19:56
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSSAM_Editor
TEMPLATE = app

LIBS += -L$$PWD/../../Librairies/SFML-2.5.1-build-debug_MinGW7.3.0-x64/lib
LIBS += -L$$PWD/../../Librairies/SFML-2.5.1-build-release_MinGW7.3.0-x64/lib

win32
{
    INCLUDEPATH += ../../Librairies/SFML-2.5.1-build-debug_MinGW7.3.0-x64/include
    DEPENDPATH += ../../Librairies/SFML-2.5.1-build-debug_MinGW7.3.0-x64/include

    CONFIG(release, debug|release): LIBS +=     -lsfml-system
    else:CONFIG(debug, debug|release): LIBS +=  -lsfml-system-d

    CONFIG(release, debug|release): LIBS +=     -lsfml-window
    else:CONFIG(debug, debug|release): LIBS +=  -lsfml-window-d

    CONFIG(release, debug|release): LIBS +=     -lsfml-graphics
    else:CONFIG(debug, debug|release): LIBS +=  -lsfml-graphics-d

    CONFIG(release, debug|release): LIBS +=     -lsfml-audio
    else:CONFIG(debug, debug|release): LIBS +=  -lsfml-audio-d
}


SOURCES += main.cpp\
        Asset.cpp \
        AssetModel.cpp \
        MainWindow.cpp \
        AnimationManager/Animation.cpp \
        AnimationManager/AnimationCreator.cpp \
        AnimationManager/AnimationManager.cpp \
        AnimationManager/AnimationModel.cpp \
        AnimationManager/AnimationViewer.cpp \
        FileManager/File.cpp \
        FileManager/FileManager.cpp \
        FileManager/FileModel.cpp \
        FileManager/FileViewer.cpp \
        ParticleManager/Particle.cpp \
        ParticleManager/ParticleCreator.cpp \
        ParticleManager/ParticleManager.cpp \
        ParticleManager/ParticleModel.cpp \
        ParticleManager/ParticleViewer.cpp \
        SpaceshipManager/SpaceshipEditor.cpp \
        WeaponManager/Weapon.cpp \
        widgets/AssetPicker.cpp \
        widgets/EntityData.cpp \
        widgets/OSSAM_World.cpp \
        widgets/QSFMLView.cpp \
        widgets/SpaceshipData.cpp \
        widgets/ClickableLabel.cpp

HEADERS  += Asset.h \
        AssetModel.h \
        MainWindow.h \
        AnimationManager/Animation.h \
        AnimationManager/AnimationCreator.h \
        AnimationManager/AnimationManager.h \
        AnimationManager/AnimationModel.h \
        AnimationManager/AnimationViewer.h \
        FileManager/File.h \
        FileManager/FileManager.h \
        FileManager/FileModel.h \
        FileManager/FileViewer.h \
        ParticleManager/Particle.h \
        ParticleManager/ParticleCreator.h \
        ParticleManager/ParticleManager.h \
        ParticleManager/ParticleModel.h \
        ParticleManager/ParticleViewer.h \
        SpaceshipManager/SpaceshipEditor.h \
        WeaponManager/Weapon.h \
        widgets/AssetPicker.h \
        widgets/EntityData.h \
        widgets/OSSAM_World.h \
        widgets/QSFMLView.h \
        widgets/SpaceshipData.h \
        widgets/ClickableLabel.h

FORMS    += MainWindow.ui \
        AnimationManager/AnimationCreator.ui \
        AnimationManager/AnimationManager.ui \
        FileManager/FileManager.ui \
        FileManager/FileViewer.ui \
        ParticleManager/ParticleCreator.ui \
        ParticleManager/ParticleManager.ui \
        SpaceshipManager/SpaceshipEditor.ui \
        widgets/AssetPicker.ui \
        widgets/EntityData.ui \
        widgets/SpaceshipData.ui

RESOURCES += \
    icons.qrc
