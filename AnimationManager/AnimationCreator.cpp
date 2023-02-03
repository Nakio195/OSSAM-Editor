#include "AnimationCreator.h"
#include "ui_AnimationCreator.h"

AnimationCreator::AnimationCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationCreator)
{
    ui->setupUi(this);
}

AnimationCreator::~AnimationCreator()
{
    delete ui;
}
