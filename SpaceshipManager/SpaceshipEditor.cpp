#include "SpaceshipEditor.h"
#include "ui_SpaceshipEditor.h"


SpaceshipEditor::SpaceshipEditor(QWidget *parent) : QWidget(parent), ui(new Ui::SpaceshipEditor)
{
    ui->setupUi(this);

}

SpaceshipEditor::~SpaceshipEditor()
{
    delete ui;
}
