#include "AnimationCreator.h"
#include "ui_AnimationCreator.h"

#include <QColorDialog>
#include "widgets/AssetPicker.h"

AnimationCreator::AnimationCreator(AssetModel *assets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationCreator),
    mAssets(assets)
{
    ui->setupUi(this);
    mTexture = File(File::Invalid);

    connect(ui->btn_Play, &QAbstractButton::clicked, ui->viewer, &AnimationViewer::play);
    connect(ui->viewer, &AnimationViewer::textureChanged, this, &AnimationCreator::textureChanged);

    ui->cmb_Mode->addItem("One Shot", QVariant(Animation::TimerMode::OneShot));
    ui->cmb_Mode->addItem("Continue", QVariant(Animation::TimerMode::Continous));
}

AnimationCreator::~AnimationCreator()
{
    delete ui;
}

void AnimationCreator::textureChanged(const sf::Texture& texture)
{
    ui->dbl_height->setValue(static_cast<int>(texture.getSize().y));
    ui->lbl_property->setText(QString("Largeur : ") + QString::number(texture.getSize().x) + " px\r\nHauteur : " + QString::number(texture.getSize().y) + " px");
}

void AnimationCreator::browseFile()
{
    mTexture = *static_cast<File*>(AssetPicker::pick(mAssets, this, Asset::Invalid));

    if(mTexture.getType() != File::Invalid)
    {
       ui->ln_Asset->setText(mTexture.getName());
       ui->viewer->setTexture(mTexture.getPath());
       mAnimation.setTextureUID(mTexture.getUID());

       if(ui->ln_Name->text() == QString(""))
       {
           ui->ln_Name->setText(mTexture.getName());
       }
    }
}

void AnimationCreator::parametersEdited()
{
    sf::IntRect rect(0, 0, ui->dbl_width->value(), ui->dbl_height->value());
    ui->viewer->setRect(rect);
    ui->viewer->setFrames(ui->dbl_frames->value());
    ui->viewer->setPeriod(static_cast<float>(ui->dbl_period->value()));

    mAnimation.setName(ui->ln_Name->text());
    mAnimation.setWidth(static_cast<unsigned int>(ui->dbl_width->value()));
    mAnimation.setHeight(static_cast<unsigned int>(ui->dbl_height->value()));
    mAnimation.setFrames(static_cast<unsigned int>(ui->dbl_frames->value()));
    mAnimation.setPeriod(static_cast<float>(ui->dbl_period->value()));
    mAnimation.setMode(Animation::TimerMode(ui->cmb_Mode->currentData().toInt()));
}

Animation AnimationCreator::getAnimation()
{
    return mAnimation;
}

void AnimationCreator::setBackgroundColor()
{
    ui->viewer->setBackgroundColor(QColorDialog::getColor());
}

Animation AnimationCreator::create(AssetModel *assets, QWidget *parent)
{
    AnimationCreator picker(assets, parent);

    assets->setType(Asset::Animation);

    if(picker.exec() == QDialog::Accepted)
        return picker.getAnimation();
    else
        return Animation();
}
