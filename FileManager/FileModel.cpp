#include "FileModel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QtAlgorithms>
#include <QColor>
#include <QBrush>
#include <QFile>
#include <QMessageBox>

FileModel::FileModel(AssetModel *assets, QObject *parent)
    : QAbstractTableModel(parent), mAssets(assets)
{

}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            switch(section)
            {
            case FileModel::ID:
                return QVariant(QString("ID"));
            case FileModel::Name:
                return QVariant(QString("Nom"));
            case FileModel::Type:
                return QVariant(QString("Type"));
            case FileModel::Path:
                return QVariant(QString("Chemin"));
            }
        }
    }

    return QVariant();
}

int FileModel::rowCount(const QModelIndex &) const
{
    return mFiles.count();
}

int FileModel::columnCount(const QModelIndex &) const
{
    return 4;
}

void FileModel::sort(int column, Qt::SortOrder order)
{
    layoutAboutToBeChanged();

    if(column == ID)
    {
        if(order == Qt::AscendingOrder)
            qSort(mFiles.begin(), mFiles.end(), [] (const File& a, const File& b) { return a.getUID() < b.getUID();});
        else
            qSort(mFiles.begin(), mFiles.end(), [] (const File& a, const File& b) { return a.getUID() > b.getUID();});
    }

    if(column == Type)
    {
        if(order == Qt::AscendingOrder)
            qSort(mFiles.begin(), mFiles.end(), [] (const File& a, const File& b) { return a.getType() < b.getType();});
        else
            qSort(mFiles.begin(), mFiles.end(), [] (const File& a, const File& b) { return a.getType() > b.getType();});
    }

    if(column == Name)
    {
        if(order == Qt::AscendingOrder)
            qSort(mFiles.begin(), mFiles.end(), [] (const File& a, const File& b) { return a.getName() < b.getName();});
        else
            qSort(mFiles.begin(), mFiles.end(), [] (const File& a, const File& b) { return a.getName() > b.getName();});
    }

    if(column == Path)
    {
        if(order == Qt::AscendingOrder)
            qSort(mFiles.begin(), mFiles.end(), [] (const File& a, const File& b) { return a.getPath() < b.getPath();});
        else
            qSort(mFiles.begin(), mFiles.end(), [] (const File& a, const File& b) { return a.getPath() > b.getPath();});
    }

    layoutChanged();
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() >= mFiles.count())
        return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch(index.column())
        {
            case FileModel::ID:
                return QVariant(QString::number(mFiles[index.row()].getUID()));
            case FileModel::Name:
                return QVariant(mFiles[index.row()].getName());
            case FileModel::Type:
                return QVariant(File::TypeToText(mFiles[index.row()].getType()));
            case FileModel::Path:
                return QVariant(mFiles[index.row()].getPath());
        }
    }

    if(role == Qt::BackgroundRole)
    {
        switch(mFiles[index.row()].getType())
        {
            case File::Texture:
            return index.row() % 2 ? QVariant(QBrush(QColor(160, 255, 160))) : QVariant(QBrush(QColor(200, 255, 200)));
            case File::Font:
            return index.row() % 2 ? QVariant(QBrush(QColor(255, 127, 127))) : QVariant(QBrush(QColor(255, 200, 200)));
            case File::Sound:
            return index.row() % 2 ? QVariant(QBrush(QColor(127, 255, 255))) : QVariant(QBrush(QColor(200, 255, 255)));
            case File::Shader:
            return index.row() % 2 ? QVariant(QBrush(QColor(127, 127, 255))) : QVariant(QBrush(QColor(200, 200, 255)));

            default:
            return QVariant();
        }
    }

    return QVariant();
}

// Edit functionality
Qt::ItemFlags FileModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
}

bool FileModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        if(index.row() < mFiles.size())
        {
            switch(index.column())
            {
                case FileModel::ID:
                    break;

                case FileModel::Name:
                    mFiles[index.row()].setName(value.toString());
                    emit dataChanged(index, index, {role});
                    return true;

                case FileModel::Type:
                    mFiles[index.row()].setType(File::TypeFromText(value.toString()));
                    emit dataChanged(index, index, {role});
                    break;

                case FileModel::Path:
                    mFiles[index.row()].setPath(value.toString());
                    emit dataChanged(index, index, {role});
                    break;

            }
        }
    }

    return false;
}

bool FileModel::insertRows(int , int , const QModelIndex &)
{
    return false;
}

bool FileModel::removeRows(int , int , const QModelIndex &)
{
    return false;
}


const QVector<File>& FileModel::getFiles()
{
    return mFiles;
}

bool FileModel::readJSON(QJsonObject &json)
{
    if(json.contains("files") && json["files"].isArray())
    {
        unsigned long long maxUID = 0;
        QJsonArray array = json["files"].toArray();

        beginResetModel();
        mFiles.clear();
        endResetModel();

        beginInsertRows(QModelIndex(), 0, array.size());

        mFiles.reserve(array.size());

        for(int row = 0; row < array.size(); row++)
        {
            QJsonObject json = array[row].toObject();
            File file;
            file.fromJSON(json);

            mFiles.push_back(file);
            mAssets->addAsset(&mFiles.last());

            if(file.getUID() > maxUID)
                maxUID = file.getUID();
        }

        File::setCurrentUID(maxUID+1);

        endInsertRows();

        return true;
    }

    return false;
}

void FileModel::writeJSON(QJsonObject& json)
{

    json.insert("count", QString::number(mFiles.count()));

    QJsonArray FileArray;
    for(auto& File : mFiles)
    {
        QJsonObject obj;
        File.toJSON(obj);
        FileArray.append(obj);
    }

    json.insert("files", FileArray);

}

const File FileModel::getFile(int row)
{
    if(row >= mFiles.count())
        return File(File::Invalid);

    return mFiles[row];
}

const File FileModel::getByUID(unsigned long long UID)
{
    for(auto& File : mFiles)
    {
        if(File.getUID() == UID)
            return File;
    }

    return File(File::Type::Invalid);
}

void FileModel::removeFile(unsigned long long uid)
{
    int row = -1;

    for(int i = 0; i < mFiles.count(); i++)
    {
        if(mFiles[i].getUID() == uid)
        {
            row = i;
            break;
        }
    }

    if(row == -1)
        return;

    beginRemoveRows(QModelIndex(), row, row);
    mFiles.removeAt(row);
    endRemoveRows();
}

void FileModel::addFile(File file)
{
    beginInsertRows(QModelIndex(), mFiles.count(), mFiles.count());
    mFiles.insert(mFiles.count(), file);
    mAssets->addAsset(&mFiles.last());
    endInsertRows();
}

unsigned long long FileModel::getUID(QModelIndex index)
{
    if(!index.isValid())
        return 0;

    return mFiles[index.row()].getUID();
}

bool FileModel::loadFromFile(QString path)
{
    QFile FilesFile(path);

    if(!FilesFile.open(QIODevice::ReadOnly))
        QMessageBox::critical(nullptr, "Erreur plutôt critique quand même", "Impossible d'accéder au fichier de sauvegarde des Files : " + path);
    else
    {
        QJsonObject Files(QJsonDocument::fromJson(FilesFile.readAll()).object());
        readJSON(Files);

        return true;
    }
    return false;
}
