#include "ParticleManager.h"
#include "ui_ParticleManager.h"

ParticleManager::ParticleManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParticleManager)
{
    ui->setupUi(this);
}

ParticleManager::~ParticleManager()
{
    delete ui;
}
