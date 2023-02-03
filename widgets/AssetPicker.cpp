#include "AssetPicker.h"
#include "ui_AssetPicker.h"

AssetPicker::AssetPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssetPicker)
{
    ui->setupUi(this);
}

AssetPicker::~AssetPicker()
{
    delete ui;
}
