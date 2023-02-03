#include "SpaceshipData.h"
#include "ui_SpaceshipData.h"

SpaceshipData::SpaceshipData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpaceshipData)
{
    ui->setupUi(this);
}

SpaceshipData::~SpaceshipData()
{
    delete ui;
}
