#include "AnimationManager.h"
#include "ui_AnimationManager.h"

#include <QMessageBox>
#include <QCloseEvent>
#include "AnimationCreator.h"

AnimationManager::AnimationManager(AssetModel* assets, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationManager),
    mAssets(assets)
{
    ui->setupUi(this);

    ui->btn_Save->setEnabled(false);

    mAssets->setType(Asset::Animation);
    ui->table->setModel(mAssets);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->table->horizontalHeader()->setSortIndicator(AssetModel::Name, Qt::AscendingOrder);
    ui->table->sortByColumn(AssetModel::Name, Qt::AscendingOrder);
    mSearchProxy.setSourceModel(mAssets);
    mSearchProxy.setFilterKeyColumn(AssetModel::Name);
    mSearchProxy.setFilterCaseSensitivity(Qt::CaseInsensitive);

    setFocusPolicy(Qt::FocusPolicy::TabFocus);

    connect(ui->table->selectionModel(), QOverload<const QModelIndex&, const QModelIndex&>::of(&QItemSelectionModel::currentRowChanged), this, &AnimationManager::selectionChanged);
    connect(ui->btn_play, &QAbstractButton::clicked, ui->viewer, &AnimationViewer::play);
}

AnimationManager::~AnimationManager()
{
    delete ui;
}

void AnimationManager::focusChange(QMdiSubWindow* window)
{
    if(window != nullptr)
    {
        if(window->widget() == this)
        {
            mAssets->setType(Asset::Animation);
            ui->table->setUpdatesEnabled(true);
        }

        else
            ui->table->setUpdatesEnabled(false);
    }
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
        ui->table->setModel(mAssets);
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

    Animation anim = mAssets->getAnimation(current.row());

    if(anim.getBaseType() != Asset::Invalid)
    {
        ui->viewer->setTexture(dynamic_cast<File*>(mAssets->getByUID(Asset::File, anim.getTextureUID()))->getPath());
        ui->viewer->setAnimation(anim);
    }
}

void AnimationManager::create()
{
    ui->table->setUpdatesEnabled(false);
    Animation anim = AnimationCreator::create(mAssets, this);
    ui->table->setUpdatesEnabled(true);

    if(anim.getName() != QString("Invalid"))
    {
        mAssets->addAnimation(anim);
        ui->btn_Save->setEnabled(true);
    }
}

void AnimationManager::remove()
{
    if(ui->table->selectionModel()->hasSelection())
    {
        Animation::UID currentUID = mAssets->getAnimation(ui->table->selectionModel()->selectedRows().first().row()).getUID();
        mAssets->removeAnimation(currentUID);
        ui->btn_Save->setEnabled(true);
    }
}

void AnimationManager::save()
{
    emit requestSave();
    ui->btn_Save->setEnabled(false);
}

