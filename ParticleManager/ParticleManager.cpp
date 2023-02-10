#include "ParticleManager.h"
#include "ui_ParticleManager.h"

#include <QMessageBox>
#include <QCloseEvent>
#include "ParticleCreator.h"

ParticleManager::ParticleManager(Context* context,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParticleManager),
    mContext(context)
{
    ui->setupUi(this);

    ui->btn_Save->setEnabled(false);

    ui->table->setModel(mContext->particles());
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->table->horizontalHeader()->setSortIndicator(ParticleModel::Name, Qt::AscendingOrder);
    ui->table->sortByColumn(ParticleModel::Name, Qt::AscendingOrder);
    mSearchProxy.setSourceModel(mContext->particles());
    mSearchProxy.setFilterKeyColumn(ParticleModel::Name);
    mSearchProxy.setFilterCaseSensitivity(Qt::CaseInsensitive);

    connect(ui->table->selectionModel(), QOverload<const QModelIndex&, const QModelIndex&>::of(&QItemSelectionModel::currentRowChanged), this, &ParticleManager::selectionChanged);
    connect(mContext->particles(), &QAbstractTableModel::dataChanged, this, &ParticleManager::selectionChanged);

    connect(ui->btn_delete, &QCommandLinkButton::clicked, this, &ParticleManager::remove);
    connect(ui->btn_add, &QCommandLinkButton::clicked, this, &ParticleManager::create);
    connect(ui->ln_search, &QLineEdit::textEdited, this, &ParticleManager::search);
    connect(ui->btn_Save, &QCommandLinkButton::clicked, this, &ParticleManager::save);
}

ParticleManager::~ParticleManager()
{
    delete ui;
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
        ui->table->setModel(mContext->particles());
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

    Particle anim = mContext->particles()->getParticle(current.row());
    ui->viewer->setTexture(mContext->files()->getByUID(anim.getTextureUID()).getPath());
    ui->viewer->setParticle(anim);
}

void ParticleManager::create()
{
    Particle anim = ParticleCreator::create(mContext, this);

    if(anim.getName() != QString("Invalid"))
    {
        mContext->particles()->addParticle(anim);
        ui->btn_Save->setEnabled(true);
    }
}

void ParticleManager::remove()
{
    if(ui->table->selectionModel()->hasSelection())
    {
        Particle::UID currentUID = mContext->particles()->getParticle(ui->table->selectionModel()->selectedRows().first().row()).getUID();
        mContext->particles()->removeParticle(currentUID);
        ui->btn_Save->setEnabled(true);
    }
}

void ParticleManager::save()
{
    emit requestSave();
    ui->btn_Save->setEnabled(false);
}
