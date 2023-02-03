#include "AnimationManager.h"
#include "ui_AnimationManager.h"

AnimationManager::AnimationManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationManager)
{
    ui->setupUi(this);
}

AnimationManager::~AnimationManager()
{
    delete ui;
}
