#include "AnimationManager.h"
#include "ui_AnimationManager.h"

#include <QMessageBox>
#include <QCloseEvent>
#include "AnimationCreator.h"

AnimationManager::AnimationManager(AnimationModel* anims, FileModel *assets,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationManager),
    mFiles(assets),
    mAnimatons(anims)
{
    ui->setupUi(this);

    ui->btn_Save->setEnabled(false);

    ui->table->setModel(mAnimatons);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->table->horizontalHeader()->setSortIndicator(AnimationModel::Name, Qt::AscendingOrder);
    ui->table->sortByColumn(AnimationModel::Name, Qt::AscendingOrder);
    mSearchProxy.setSourceModel(mAnimatons);
    mSearchProxy.setFilterKeyColumn(AnimationModel::Name);
    mSearchProxy.setFilterCaseSensitivity(Qt::CaseInsensitive);

    connect(ui->table->selectionModel(), QOverload<const QModelIndex&, const QModelIndex&>::of(&QItemSelectionModel::currentRowChanged), this, &AnimationManager::selectionChanged);
    connect(ui->btn_play, &QAbstractButton::clicked, ui->viewer, &AnimationViewer::play);
}

AnimationManager::~AnimationManager()
{
    delete ui;
}

void AnimationManager::closeEvent(QCloseEvent *event)
{
    if(ui->btn_Save->isEnabled())
    {
        auto answer = QMessageBox::question(this, "Sauvegarde avant fermeture", "Les données ont été modifiées, voulez vous vraiment fermer sans sauvegrader ?");

        if(answer == QMessageBox::Yes)
            event->accept();
        else
            event->ignore();
    }

    else
        event->accept();
}


void AnimationManager::search(QString string)
{
    if(string == QString(""))
    {
        ui->table->setModel(mAnimatons);
    }

    else
    {
        mSearchProxy.setFilterFixedString(string);
        ui->table->setModel(&mSearchProxy);
    }
}

void AnimationManager::selectionChanged(const QModelIndex &current, const QModelIndex &)
{
    if(!current.isValid())
        return;

    Animation anim = mAnimatons->getAnimation(current.row());
    ui->viewer->setTexture(mFiles->getByUID(anim.getTextureUID()).getPath());
    ui->viewer->setAnimation(anim);
}

void AnimationManager::create()
{
    Animation anim = AnimationCreator::create(mFiles, this);

    if(anim.getName() != QString("Invalid"))
    {
        mAnimatons->addAnimation(anim);
        ui->btn_Save->setEnabled(true);
    }
}

void AnimationManager::remove()
{
    if(ui->table->selectionModel()->hasSelection())
    {
        Animation::UID currentUID = mAnimatons->getAnimation(ui->table->selectionModel()->selectedRows().first().row()).getUID();
        mAnimatons->removeAnimation(currentUID);
        ui->btn_Save->setEnabled(true);
    }
}

void AnimationManager::save()
{
    emit requestSave();
    ui->btn_Save->setEnabled(false);
}
