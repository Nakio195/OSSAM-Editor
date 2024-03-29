#include "FileManager.h"
#include "ui_FileManager.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSound>
#include <QFileInfo>
#include <QTime>
#include <QJsonDocument>
#include <QAudioDeviceInfo>
#include <QCloseEvent>


FileManager::FileManager(Context *context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManager),
    mContext(context)
{
    ui->setupUi(this);

    mCurrentUID = 0;
    mPendingChanges = false;

    mMapper.setModel(mContext->files());
    mMapper.addMapping(ui->ln_UID, FileModel::ID);
    mMapper.addMapping(ui->ln_Name, FileModel::Name);
    mMapper.addMapping(ui->ln_Path, FileModel::Path);

    ui->tableView->setModel(mContext->files());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSortIndicator(FileModel::Type, Qt::AscendingOrder);
    ui->tableView->sortByColumn(FileModel::Type, Qt::AscendingOrder);
    mSearchProxy.setSourceModel(mContext->files());
    mSearchProxy.setFilterKeyColumn(FileModel::Name);
    mSearchProxy.setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->grp_Mapper->setEnabled(false);

    setFocusPolicy(Qt::FocusPolicy::TabFocus);

    connect(ui->tableView->selectionModel(), QOverload<const QModelIndex&, const QModelIndex&>::of(&QItemSelectionModel::currentRowChanged), this, &FileManager::selectionChanged);
    connect(mContext->files(), &AssetModel::dataChanged, this, &FileManager::saveChanges);
}

FileManager::~FileManager()
{
    delete ui;
}

void FileManager::focusChange(QMdiSubWindow* window)
{
    if(window != nullptr)
    {
        if(window->widget() == this)
        {
            ui->tableView->setUpdatesEnabled(true);
        }

        else
            ui->tableView->setUpdatesEnabled(false);
    }
}

void FileManager::closeEvent(QCloseEvent *event)
{
    if(ui->btn_save->isEnabled())
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

bool FileManager::saveToFile()
{
    emit requestSave();

    ui->btn_save->setEnabled(false);
    return true;
}

void FileManager::selectionChanged(const QModelIndex &current, const QModelIndex &)
{
    if(!current.isValid())
        return;

    rowChanged(current);
}

void FileManager::rowChanged(QModelIndex index)
{    
    ui->grp_Mapper->setEnabled(true);

    if(ui->ln_search->text() == QString(""))
    {
        mCurrentUID = mContext->files()->getUID(index);
        mMapper.setCurrentIndex(index.row());
    }

    else
    {
        mCurrentUID = mContext->files()->getUID(mSearchProxy.mapToSource(index));
        mMapper.setCurrentIndex(mSearchProxy.mapToSource(index).row());
    }

    updateViewer();
}

void FileManager::saveChanges()
{
    ui->btn_save->setEnabled(true);
}

void FileManager::search(QString string)
{
    if(string == QString(""))
        ui->tableView->setModel(mContext->files());

    else
    {
        mSearchProxy.setFilterFixedString(string);
        ui->tableView->setModel(&mSearchProxy);
    }
}

QString FileManager::browse()
{
    return QFileDialog::getOpenFileName(this, tr("Sélectionner une ressource"), "./Ressources", tr("Ressources (*.png *.jpg *.bmp *.ttf *.ogg *.wav *.sha)"));
}

void FileManager::browseForFile()
{
    QString path = browse();

    if(path == QString(""))
        return;

    QDir dir;
    path = dir.relativeFilePath(path);
    ui->ln_Path->setText(path);
    mMapper.submit();

    updateViewer();

    return;
}

void FileManager::createFile()
{
    QString path = browse();
    QString name;
    Asset::Type type;

    // Autodeduce type and name from browsed file
    if(path.contains(QString("png")) || path.contains(QString("jpg")) || path.contains(QString("bmp")))
        type = File::Texture;
    else if(path.contains(QString("ttf")))
        type = File::Font;
    else if(path.contains(QString("ogg")) || path.contains(QString("wav")))
        type = File::Sound;
    else if(path.contains(QString("sha")))
        type = File::Shader;
    else
        type = File::Invalid;

    QFileInfo infos(path);
    name = infos.baseName();
    QDir dir;
    path = dir.relativeFilePath(path);

    File newFile(type, name, path);
    mContext->files()->addFile(newFile);
    saveChanges();
}

void FileManager::removeFile()
{
    if(mCurrentUID == 0)
        return;

    QString name = mContext->files()->getByUID(mCurrentUID).getName();
    auto answer = QMessageBox::question(this, "Confirmation", "Voulez vous supprimer " + name + " ?");

    if(answer == QMessageBox::Yes)
    {
       mContext->files()->removeFile(mCurrentUID);
       mCurrentUID = 0;
       ui->grp_Mapper->setEnabled(false);
       mMapper.setCurrentIndex(0);
       ui->fileViewer->hideViewers();

       ui->btn_save->setEnabled(true);
    }
}

void FileManager::updateViewer()
{
    if(mCurrentUID == 0)
        return;
    File asset = mContext->files()->getByUID(mCurrentUID);

    ui->fileViewer->setFile(asset);
}

