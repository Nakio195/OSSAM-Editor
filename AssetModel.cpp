#include "AssetModel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

AssetModel::AssetModel(QObject *parent) : QAbstractTableModel(parent)
{
}

QVariant AssetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            switch(section)
            {
            case AssetModel::ID:
                return QVariant(QString("ID"));
            case AssetModel::Name:
                return QVariant(QString("Nom"));
            case AssetModel::Type:
                return QVariant(QString("Type"));
            }
        }
    }

    return QVariant();
}

int AssetModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return mAssets.count();
    // FIXME: Implement me!
}

int AssetModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 2;
    // FIXME: Implement me!
}


void AssetModel::sort(int column, Qt::SortOrder order)
{
    layoutAboutToBeChanged();

    if(column == ID)
    {
        if(order == Qt::AscendingOrder)
            qSort(mAssets.begin(), mAssets.end(), [] (const Asset& a, const Asset& b) { return a.getUID() < b.getUID();});
        else
            qSort(mAssets.begin(), mAssets.end(), [] (const Asset& a, const Asset& b) { return a.getUID() > b.getUID();});
    }

    if(column == Name)
    {
        if(order == Qt::AscendingOrder)
            qSort(mAssets.begin(), mAssets.end(), [] (const Asset& a, const Asset& b) { return a.getName() < b.getName();});
        else
            qSort(mAssets.begin(), mAssets.end(), [] (const Asset& a, const Asset& b) { return a.getName() > b.getName();});
    }

    layoutChanged();
}

QVariant AssetModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() >= mAssets.count())
        return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch(index.column())
        {
            case AssetModel::ID:
                return QVariant(QString::number(mAssets[index.row()].getUID()));
            case AssetModel::Name:
                return QVariant(mAssets[index.row()].getName());
        }
    }
    return QVariant();
}

bool AssetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        if(index.row() < mAssets.size())
        {
            switch(index.column())
            {
                case AssetModel::ID:
                    break;

                case AssetModel::Name:
                    mAssets[index.row()].setName(value.toString());
                    emit dataChanged(index, index, {role});
                    return true;
            }
        }
    }

    return false;
}

Qt::ItemFlags AssetModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if(index.column() == AssetModel::Name)
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;

    return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
}

bool AssetModel::insertRows(int , int , const QModelIndex &)
{
    return false;
}

bool AssetModel::insertColumns(int , int , const QModelIndex &)
{
    return false;
}


const QVector<Asset>& AssetModel::getAssets()
{
    return mAssets;
}

bool AssetModel::readJSON(QJsonObject &json)
{
    if(json.contains("Assets") && json["Assets"].isArray())
    {
        unsigned long long maxUID = 0;
        QJsonArray array = json["Assets"].toArray();

        beginResetModel();
        mAssets.clear();
        endResetModel();

        beginInsertRows(QModelIndex(), 0, array.size());

        mAssets.reserve(array.size());

        for(int row = 0; row < array.size(); row++)
        {
            QJsonObject json = array[row].toObject();
            Asset asset;
            asset.fromJSON(json);

            mAssets.push_back(asset);

            if(asset.getUID() > maxUID)
                maxUID = asset.getUID();
        }

        Asset::setCurrentUID(maxUID+1);

        endInsertRows();

        return true;
    }

    return false;
}

void AssetModel::writeJSON(QJsonObject& json)
{
    json.insert("count", QString::number(mAssets.count()));

    QJsonArray animArray;
    for(auto& Asset : mAssets)
    {
        QJsonObject obj;
        Asset.toJSON(obj);
        animArray.append(obj);
    }

    json.insert("Assets", animArray);

}

const Asset AssetModel::getAsset(int row)
{
    if(row >= mAssets.count())
        return Asset();

    return mAssets[row];
}

const Asset AssetModel::getByUID(Asset::UID uid)
{
    for(auto& anim : mAssets)
    {
        if(anim.getUID() == uid)
            return anim;
    }

    return Asset();
}

void AssetModel::removeAsset(Asset::UID uid)
{
    int row = -1;

    for(int i = 0; i < mAssets.count(); i++)
    {
        if(mAssets[i].getUID() == uid)
        {
            row = i;
            break;
        }
    }

    if(row == -1)
        return;

    beginRemoveRows(QModelIndex(), row, row);
    mAssets.removeAt(row);
    endRemoveRows();
}

void AssetModel::addAsset(Asset anim)
{
    beginInsertRows(QModelIndex(), mAssets.count(), mAssets.count());
    mAssets.insert(mAssets.count(), anim);
    endInsertRows();
}

unsigned long long AssetModel::getUID(QModelIndex index)
{
    if(!index.isValid())
        return 0;

    return mAssets[index.row()].getUID();
}

bool AssetModel::loadFromFile(QString path)
{
    QFile AnimFile(path);

    if(!AnimFile.open(QIODevice::ReadOnly))
        QMessageBox::critical(nullptr, "Erreur plutôt critique quand même", "Impossible d'accéder au fichier de sauvegarde des Assets : " + path);
    else
    {
        QJsonObject Assets(QJsonDocument::fromJson(AnimFile.readAll()).object());
        readJSON(Assets);

        return true;
    }
    return false;
}

