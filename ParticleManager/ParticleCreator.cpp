#include "ParticleCreator.h"
#include "ui_ParticleCreator.h"

ParticleCreator::ParticleCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParticleCreator)
{
    ui->setupUi(this);
}

ParticleCreator::~ParticleCreator()
{
    delete ui;
}
