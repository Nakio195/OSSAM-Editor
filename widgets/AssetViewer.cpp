#include "AssetViewer.h"
#include "ui_AssetViewer.h"

AssetViewer::AssetViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssetViewer)
{
    ui->setupUi(this);
}

AssetViewer::~AssetViewer()
{
    delete ui;
}
