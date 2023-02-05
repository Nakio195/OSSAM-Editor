#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>
#include <QMessageBox>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    JSON_AnimationPath = QString("data/animations.json");
    JSON_AssetPath = QString("data/assets.json");
    JSON_ParticlePath = QString("data/particles.json");
    mAssets.loadFromFile(JSON_AssetPath);
    mAssets.loadFromFile(JSON_AnimationPath);
    mAssets.loadFromFile(JSON_ParticlePath);

    mFileManager = nullptr;
    mAnimationManager = nullptr;
    mParticleManager = nullptr;

    ui->setupUi(this);

    connect(ui->actionAssets_Manager, &QAction::triggered, this, &MainWindow::openAssetManager);
    connect(ui->actionAnimations, &QAction::triggered, this, &MainWindow::openAnimationEditor);
    connect(ui->actionParticles, &QAction::triggered, this, &MainWindow::openParticleManager);
    //connect(ui->MdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::windowChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::windowChanged(QMdiSubWindow *window)
{
    if(window != nullptr)
    {
        if(window->widget() == mFileManager)
        {
            mAssets.setType(Asset::File);
        }

        if(window->widget() == mAnimationManager)
        {
            mAssets.setType(Asset::Animation);
        }

        if(window->widget() == mParticleManager)
        {
            mAssets.setType(Asset::Particle);
        }
    }
}

void MainWindow::openAssetManager()
{
    if(mFileManager != nullptr)
    {
        mFileManager->setFocus();
        return;
    }

    else
    {
        mFileManager = new FileManager(&mAssets);
        connect(mFileManager, &FileManager::requestSave, this, &MainWindow::saveAssets);
        connect(mFileManager, &FileManager::destroyed, this, &MainWindow::closeAssetManager);
        connect(ui->MdiArea, &QMdiArea::subWindowActivated, mFileManager, &FileManager::focusChange);
        ui->MdiArea->addSubWindow(mFileManager);
        mFileManager->show();
    }
}

void MainWindow::closeAssetManager()
{
    mFileManager = nullptr;
}


void MainWindow::openParticleManager()
{
    if(mParticleManager != nullptr)
    {
        mParticleManager->setFocus();
        return;
    }

    else
    {
        mParticleManager = new ParticleManager(&mAssets);
        connect(mParticleManager, &ParticleManager::requestSave, this, &MainWindow::saveParticles);
        connect(mParticleManager, &ParticleManager::destroyed, this, &MainWindow::closeParticleManager);
        connect(ui->MdiArea, &QMdiArea::subWindowActivated, mParticleManager, &ParticleManager::focusChange);
        ui->MdiArea->addSubWindow(mParticleManager);
        mParticleManager->show();
    }
}

void MainWindow::closeParticleManager()
{
    mParticleManager = nullptr;
}


void MainWindow::openAnimationEditor()
{
    if(mAnimationManager != nullptr)
    {
        mAnimationManager->setFocus();
        return;
    }

    else
    {
        mAnimationManager = new AnimationManager(&mAssets);
        connect(mAnimationManager, &AnimationManager::requestSave, this, &MainWindow::saveAnimations);
        connect(mAnimationManager, &AnimationManager::destroyed, this, &MainWindow::closeAnimationEditor);
        connect(ui->MdiArea, &QMdiArea::subWindowActivated, mAnimationManager, &AnimationManager::focusChange);
        ui->MdiArea->addSubWindow(mAnimationManager);
        mAnimationManager->show();
    }
}

void MainWindow::closeAnimationEditor()
{
    mAnimationManager = nullptr;
}

void MainWindow::saveAssets()
{
    QString path(JSON_AssetPath);
    QFile AssetsFile(path);

    AssetsFile.open(QIODevice::ReadWrite);

    QJsonObject assets;
    mAssets.writeJSON(Asset::File, assets);

    QJsonDocument saveDoc(assets);
    AssetsFile.write(saveDoc.toJson());
}


void MainWindow::saveAnimations()
{
    QString path(JSON_AnimationPath);
    QFile AnimationFile(path);

    AnimationFile.open(QIODevice::ReadWrite);

    QJsonObject anims;
    mAssets.writeJSON(Asset::Animation, anims);

    QJsonDocument saveDoc(anims);
    AnimationFile.write(saveDoc.toJson());
}


void MainWindow::saveParticles()
{
    QString path(JSON_ParticlePath);
    QFile ParticleFile(path);

    ParticleFile.open(QIODevice::ReadWrite);

    QJsonObject particles;
    mAssets.writeJSON(Asset::Particle, particles);

    QJsonDocument saveDoc(particles);
    ParticleFile.write(saveDoc.toJson());
}
