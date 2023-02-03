#include "AssetManager.h"
#include "ui_AssetManager.h"

AssetManager::AssetManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssetManager)
{
    ui->setupUi(this);
}

AssetManager::~AssetManager()
{
    delete ui;
}
