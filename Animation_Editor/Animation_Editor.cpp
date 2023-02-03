#include "Animation_Editor.h"
#include "ui_Animation_Editor.h"

Animation_Editor::Animation_Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Animation_Editor)
{
    ui->setupUi(this);
}

Animation_Editor::~Animation_Editor()
{
    delete ui;
}
