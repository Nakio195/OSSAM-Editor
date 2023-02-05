#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMdiSubWindow>
#include "widgets/OSSAM_World.h"

#include "FileManager/FileManager.h"
#include "FileManager/FileModel.h"
#include "widgets/AssetPicker.h"

#include "AnimationManager/AnimationManager.h"
#include "AnimationManager/AnimationModel.h"

#include "ParticleManager/ParticleModel.h"
#include "ParticleManager/ParticleManager.h"



namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    public slots:
        void windowChanged(QMdiSubWindow *window);

    private slots:
        void saveAssets();
        void openAssetManager();
        void closeAssetManager();

        void saveAnimations();
        void openAnimationEditor();
        void closeAnimationEditor();

        void saveParticles();
        void openParticleManager();
        void closeParticleManager();


    private:
        Ui::MainWindow *ui;

        OSSAM::World *mWorld;

        AssetModel mAssets;

        FileManager* mFileManager;
        AnimationManager *mAnimationManager;
        ParticleManager *mParticleManager;

        QString JSON_AssetPath;
        QString JSON_AnimationPath;
        QString JSON_ParticlePath;
};

#endif // MAINWINDOW_H
