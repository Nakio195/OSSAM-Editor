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
    mContext.files()->loadFromFile(JSON_AssetPath);
    mContext.animations()->loadFromFile(JSON_AnimationPath);
    mContext.particles()->loadFromFile(JSON_ParticlePath);

    mFileManager = nullptr;
    mAnimationManager = nullptr;
    mParticleManager = nullptr;

    ui->setupUi(this);

    connect(ui->actionAssets_Manager, &QAction::triggered, this, &MainWindow::openAssetManager);
    connect(ui->actionAnimations, &QAction::triggered, this, &MainWindow::openAnimationEditor);
    connect(ui->actionParticles, &QAction::triggered, this, &MainWindow::openParticleManager);
}

MainWindow::~MainWindow()
{
    delete ui;
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
        mFileManager = new FileManager(&mContext);
        connect(mFileManager, &FileManager::requestSave, this, &MainWindow::saveAssets);
        connect(mFileManager, &FileManager::destroyed, this, &MainWindow::closeAssetManager);
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
        mParticleManager = new ParticleManager(&mContext);
        connect(mParticleManager, &ParticleManager::requestSave, this, &MainWindow::saveParticles);
        connect(mParticleManager, &ParticleManager::destroyed, this, &MainWindow::closeParticleManager);
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
        mAnimationManager = new AnimationManager(&mContext);
        connect(mAnimationManager, &AnimationManager::requestSave, this, &MainWindow::saveAnimations);
        connect(mAnimationManager, &AnimationManager::destroyed, this, &MainWindow::closeAnimationEditor);
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
    mContext.files()->writeJSON(assets);

    QJsonDocument saveDoc(assets);
    AssetsFile.write(saveDoc.toJson());
}


void MainWindow::saveAnimations()
{
    QString path(JSON_AnimationPath);
    QFile AnimationFile(path);

    AnimationFile.open(QIODevice::ReadWrite);

    QJsonObject anims;
    mContext.animations()->writeJSON(anims);

    QJsonDocument saveDoc(anims);
    AnimationFile.write(saveDoc.toJson());
}


void MainWindow::saveParticles()
{
    QString path(JSON_ParticlePath);
    QFile ParticleFile(path);

    ParticleFile.open(QIODevice::ReadWrite);

    QJsonObject particles;
    mContext.particles()->writeJSON(particles);

    QJsonDocument saveDoc(particles);
    ParticleFile.write(saveDoc.toJson());
}
