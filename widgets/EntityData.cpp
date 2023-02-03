#include "EntityData.h"
#include "ui_EntityData.h"

EntityData::EntityData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityData)
{
    ui->setupUi(this);
}

EntityData::~EntityData()
{
    delete ui;
}
