#include "ParticleCreator.h"
#include "ui_ParticleCreator.h"

#include "widgets/AssetPicker.h"
#include <QColorDialog>

ParticleCreator::ParticleCreator(Context *context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParticleCreator),
    mContext(context)
{
    ui->setupUi(this);
    ui->clr_viewer->setAutoFillBackground(true);
}

ParticleCreator::~ParticleCreator()
{
    delete ui;
}

Particle ParticleCreator::getParticle()
{
    return std::move(mParticle);
}

void ParticleCreator::setText(QString string)
{
    mParticle.setName(string);
}

void ParticleCreator::setLifeTime(int life)
{
    mParticle.setLifeTime(static_cast<float>(life/1000.f));
}

void ParticleCreator::pickColor()
{
    QColor color = QColorDialog::getColor(mParticle.getColor());

    QPalette Palette;
    Palette.setColor(QPalette::Window, color);
    ui->clr_viewer->setPalette(Palette);

    mParticle.setColor(color);
}

void ParticleCreator::browseAsset()
{
    File temp = mContext->files()->getByUID(AssetPicker::pick(mContext, this, Asset::Texture));
    mParticle.setTextureUID(temp.getUID());
    ui->ln_texture->setText(temp.getName());
}

Particle ParticleCreator::create(Context* context, QWidget *parent)
{
    ParticleCreator picker(context, parent);

    if(picker.exec() == QDialog::Accepted)
        return picker.getParticle();
    else
        return Particle();
}
