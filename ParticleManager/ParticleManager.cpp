#include "ParticleManager.h"
#include "ui_ParticleManager.h"

#include <QMessageBox>
#include <QCloseEvent>
#include "ParticleCreator.h"

ParticleManager::ParticleManager(AssetModel* assets, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParticleManager),
    mAssets(assets)
{
    ui->setupUi(this);

    mAssets->setType(Asset::Particle);
    ui->btn_Save->setEnabled(false);

    ui->table->setModel(mAssets);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->table->horizontalHeader()->setSortIndicator(AssetModel::Name, Qt::AscendingOrder);
    ui->table->sortByColumn(AssetModel::Name, Qt::AscendingOrder);
    mSearchProxy.setSourceModel(mAssets);
    mSearchProxy.setFilterKeyColumn(AssetModel::Name);
    mSearchProxy.setFilterCaseSensitivity(Qt::CaseInsensitive);

    setFocusPolicy(Qt::FocusPolicy::TabFocus);

    connect(ui->table->selectionModel(), QOverload<const QModelIndex&, const QModelIndex&>::of(&QItemSelectionModel::currentRowChanged), this, &ParticleManager::selectionChanged);
    connect(mAssets, &QAbstractTableModel::dataChanged, this, &ParticleManager::selectionChanged);

    connect(ui->btn_delete, &QCommandLinkButton::clicked, this, &ParticleManager::remove);
    connect(ui->btn_add, &QCommandLinkButton::clicked, this, &ParticleManager::create);
    connect(ui->ln_search, &QLineEdit::textEdited, this, &ParticleManager::search);
    connect(ui->btn_Save, &QCommandLinkButton::clicked, this, &ParticleManager::save);
}

ParticleManager::~ParticleManager()
{
    delete ui;
}

void ParticleManager::focusChange(QMdiSubWindow* window)
{
    if(window != nullptr)
    {
        if(window->widget() == this)
        {
            mAssets->setType(Asset::Particle);
            ui->table->setUpdatesEnabled(true);
        }

        else
            ui->table->setUpdatesEnabled(false);
    }
}

void ParticleManager::closeEvent(QCloseEvent *event)
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


void ParticleManager::search(QString string)
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

void ParticleManager::selectionChanged(const QModelIndex &current, const QModelIndex &)
{
    if(!current.isValid())
        return;

    Particle anim = mAssets->getParticle(current.row());

    if(anim.getBaseType() != Asset::Invalid)
    {
        ui->viewer->setTexture(dynamic_cast<File*>(mAssets->getByUID(Asset::File, anim.getTextureUID()))->getPath());
        ui->viewer->setParticle(anim);
    }
}

void ParticleManager::create()
{
    Particle anim = ParticleCreator::create(mAssets, this);

    if(anim.getName() != QString("Invalid"))
    {
        mAssets->addParticle(anim);
        ui->btn_Save->setEnabled(true);
    }
}

void ParticleManager::remove()
{
    if(ui->table->selectionModel()->hasSelection())
    {
        Particle::UID currentUID = mAssets->getParticle(ui->table->selectionModel()->selectedRows().first().row()).getUID();
        mAssets->removeParticle(currentUID);
        ui->btn_Save->setEnabled(true);
    }
}

void ParticleManager::save()
{
    emit requestSave();
    ui->btn_Save->setEnabled(false);
}


