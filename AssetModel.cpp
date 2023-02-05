#include "AssetModel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

AssetModel::AssetModel(QObject *parent) : QAbstractTableModel(parent)
{
    mType = Asset::Type::Invalid;
}

void AssetModel::setType(unsigned int type)
{
    layoutAboutToBeChanged();
    mType = type;
    layoutChanged();
}

QVariant AssetModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            if(mType == Asset::Invalid)
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

            else if(mType == Asset::File)
            {
                switch(section)
                {
                case AssetModel::ID:
                    return QVariant(QString("ID"));
                case AssetModel::Name:
                    return QVariant(QString("Nom"));
                case AssetModel::Type:
                    return QVariant(QString("Type"));
                case AssetModel::Path:
                    return QVariant(QString("Chemin"));
                }
            }

            else if(mType == Asset::Animation)
            {
                switch(section)
                {
                case AssetModel::ID:
                    return QVariant(QString("ID"));
                case AssetModel::Name:
                    return QVariant(QString("Nom"));
                case AssetModel::TextureUID:
                    return QVariant(QString("Texture ID"));
                case AssetModel::FrameCount:
                    return QVariant(QString("Images"));
                case AssetModel::RectWidth:
                    return QVariant(QString("Largeur"));
                case AssetModel::RectHeight:
                    return QVariant(QString("Hauteur"));
                case AssetModel::Period:
                    return QVariant(QString("Periode"));
                case AssetModel::TimerMode:
                    return QVariant(QString("Timer Mode"));
                }
            }

            else if(mType == Asset::Particle)
            {
                switch(section)
                {
                case AssetModel::ID:
                    return QVariant(QString("ID"));
                case AssetModel::Name:
                    return QVariant(QString("Nom"));
                case AssetModel::TextureUID:
                    return QVariant(QString("Texture ID"));
                case AssetModel::LifeTime:
                    return QVariant(QString("Temps de vie"));
                case AssetModel::Color:
                    return QVariant(QString("Couleur"));
                }
            }
        }
    }

    return QVariant();
}

int AssetModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    switch(mType)
    {
        case Asset::Invalid:
            return mAnimations.count() + mFiles.count() + mParticles.count();
        case Asset::File:
            return mFiles.count();
        case Asset::Animation:
            return mAnimations.count();
        case Asset::Particle:
            return mParticles.count();
    }

    return 0;
}

int AssetModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    switch(mType)
    {
        case Asset::Invalid:
            return 3;
        case Asset::File:
            return 4;
        case Asset::Animation:
            return 8;
        case Asset::Particle:
            return 5;
    }

    return 0;
}


void AssetModel::sort(int column, Qt::SortOrder order)
{
    layoutAboutToBeChanged();

    if(mType == Asset::Invalid)
    {
        if(column == ID)
        {
            if(order == Qt::AscendingOrder)
                qSort(mAssets.begin(), mAssets.end(), [] (const Asset* a, const Asset* b) { return a->getUID() < b->getUID();});
            else
                qSort(mAssets.begin(), mAssets.end(), [] (const Asset* a, const Asset* b) { return a->getUID() > b->getUID();});
        }

        if(column == Name)
        {
            if(order == Qt::AscendingOrder)
                qSort(mAssets.begin(), mAssets.end(), [] (const Asset* a, const Asset* b) { return a->getName() < b->getName();});
            else
                qSort(mAssets.begin(), mAssets.end(), [] (const Asset* a, const Asset* b) { return a->getName() > b->getName();});
        }
    }

    else if(mType == Asset::File)
    {
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
    }

    else if(mType == Asset::Animation)
    {
        if(column == ID)
        {
            if(order == Qt::AscendingOrder)
                qSort(mAnimations.begin(), mAnimations.end(), [] (const Animation& a, const Animation& b) { return a.getUID() < b.getUID();});
            else
                qSort(mAnimations.begin(), mAnimations.end(), [] (const Animation& a, const Animation& b) { return a.getUID() > b.getUID();});
        }

        if(column == Name)
        {
            if(order == Qt::AscendingOrder)
                qSort(mAnimations.begin(), mAnimations.end(), [] (const Animation& a, const Animation& b) { return a.getName() < b.getName();});
            else
                qSort(mAnimations.begin(), mAnimations.end(), [] (const Animation& a, const Animation& b) { return a.getName() > b.getName();});
        }
    }

    else if(mType == Asset::Particle)
    {
        if(column == ID)
        {
            if(order == Qt::AscendingOrder)
                qSort(mParticles.begin(), mParticles.end(), [] (const Particle& a, const Particle& b) { return a.getUID() < b.getUID();});
            else
                qSort(mParticles.begin(), mParticles.end(), [] (const Particle& a, const Particle& b) { return a.getUID() > b.getUID();});
        }

        if(column == Name)
        {
            if(order == Qt::AscendingOrder)
                qSort(mParticles.begin(), mParticles.end(), [] (const Particle& a, const Particle& b) { return a.getName() < b.getName();});
            else
                qSort(mParticles.begin(), mParticles.end(), [] (const Particle& a, const Particle& b) { return a.getName() > b.getName();});
        }

    }

    layoutChanged();
}

QVariant AssetModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(mType == Asset::Invalid && index.row() < mAssets.count())
        {
            switch(index.column())
            {
                case AssetModel::ID:
                    return QVariant(QString::number(mAssets[index.row()]->getUID()));
                case AssetModel::Name:
                    return QVariant(mAssets[index.row()]->getName());
                case AssetModel::Type:
                    return QVariant(Asset::TypeToText(mAssets[index.row()]->getBaseType()));
            }
        }


        else if(mType == Asset::File && index.row() < mFiles.count())
        {
            switch(index.column())
            {
                case AssetModel::ID:
                    return QVariant(QString::number(mFiles[index.row()].getUID()));
                case AssetModel::Name:
                    return QVariant(mFiles[index.row()].getName());
                case AssetModel::Type:
                    return QVariant(File::TypeToText(mFiles[index.row()].getType()));
                case AssetModel::Path:
                    return QVariant(mFiles[index.row()].getPath());
            }

        }

        else if(mType == Asset::Animation && index.row() < mAnimations.count())
        {
            switch(index.column())
            {
                case AssetModel::ID:
                    return QVariant(QString::number(mAnimations[index.row()].getUID()));
                case AssetModel::Name:
                    return QVariant(mAnimations[index.row()].getName());
                case AssetModel::TextureUID:
                    return QVariant(mAnimations[index.row()].getTextureUID());
                case AssetModel::FrameCount:
                    return QVariant(mAnimations[index.row()].getFrames());
                case AssetModel::RectWidth:
                    return QVariant(mAnimations[index.row()].getWidth());
                case AssetModel::RectHeight:
                    return QVariant(mAnimations[index.row()].getHeight());
                case AssetModel::Period:
                    return QVariant(mAnimations[index.row()].getPeriod());
                case AssetModel::TimerMode:
                    switch(mAnimations[index.row()].getMode())
                    {
                        case Animation::OneShot:
                            return QVariant(QString("One shot"));
                        case Animation::Continous:
                            return QVariant(QString("Continu"));
                    }
                    break;
            }
        }

        else if(mType == Asset::Particle && index.row() < mParticles.count())
        {
            switch(index.column())
            {
                case AssetModel::ID:
                    return QVariant(QString::number(mParticles[index.row()].getUID()));
                case AssetModel::Name:
                    return QVariant(mParticles[index.row()].getName());
                case AssetModel::TextureUID:
                    return QVariant(mParticles[index.row()].getTextureUID());
                case AssetModel::LifeTime:
                    return QVariant(mParticles[index.row()].getLifeTime());
                case AssetModel::Color:
                    return QVariant(mParticles[index.row()].getColor());
            }
        }
    }

    if(role == Qt::BackgroundRole)
    {
        if(mType == Asset::File)
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

        if(mType == Asset::Animation)
        {
            if(role == Qt::BackgroundRole)
               return index.row() % 2 ? QVariant(QBrush(QColor(0, 140, 255))) : QVariant(QBrush(QColor(100, 180, 255)));
        }

        if(mType == Asset::Particle)
        {
            if(role == Qt::BackgroundRole && index.column() == AssetModel::Color)
                return QVariant(QBrush(mParticles[index.row()].getColor()));
        }

    }

    return QVariant();
}

bool AssetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        if(mType == Asset::Invalid && index.row() < mAssets.size())
        {
            switch(index.column())
            {
                case AssetModel::ID:
                    break;

                case AssetModel::Name:
                    mAssets[index.row()]->setName(value.toString());
                    emit dataChanged(index, index, {role});
                    return true;
            }
        }

        if(mType == Asset::File && index.row() < mFiles.size())
        {
            switch(index.column())
            {
                case AssetModel::ID:
                    break;

                case AssetModel::Name:
                    mFiles[index.row()].setName(value.toString());
                    emit dataChanged(index, index, {role});
                    return true;

                case AssetModel::Type:
                    mFiles[index.row()].setType(File::TypeFromText(value.toString()));
                    emit dataChanged(index, index, {role});
                    break;

                case AssetModel::Path:
                    mFiles[index.row()].setPath(value.toString());
                    emit dataChanged(index, index, {role});
                    break;
            }
        }

        if(mType == Asset::Animation && index.row() < mAnimations.size())
        {
            switch(index.column())
            {
                case AssetModel::ID:
                    break;

                case AssetModel::Name:
                    mAnimations[index.row()].setName(value.toString());
                    emit dataChanged(index, index, {role});
                    return true;
            }
        }

        if(mType == Asset::Particle && index.row() < mParticles.size())
        {
            switch(index.column())
            {
                case AssetModel::ID:
                    break;

                case AssetModel::Name:
                    mParticles[index.row()].setName(value.toString());
                    emit dataChanged(index, index, {role});
                    return true;

                case AssetModel::LifeTime:
                    mParticles[index.row()].setLifeTime(value.toFloat());
                    emit dataChanged(index, index, {role});
                    return true;

                case AssetModel::Color:
                    mParticles[index.row()].setColor(QColor(value.toString()));
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

    if(mType == Asset::Particle)
    {
        if(index.column() == AssetModel::Name)
            return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
        if(index.column() == AssetModel::LifeTime)
            return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
        if(index.column() == AssetModel::Color)
            return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }

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


const QVector<Asset*>& AssetModel::getAssets()
{
    return mAssets;
}

bool AssetModel::readJSON(QJsonObject &json)
{
    bool success = false;

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
            mAssets.push_back(&mFiles.last());

            if(file.getUID() > maxUID)
                maxUID = file.getUID();
        }

        Asset::setCurrentUID(maxUID+1);

        success = true;
        endInsertRows();
    }

    if(json.contains("animations") && json["animations"].isArray())
    {
        unsigned long long maxUID = 0;
        QJsonArray array = json["animations"].toArray();

        beginResetModel();
        mAnimations.clear();
        endResetModel();

        beginInsertRows(QModelIndex(), 0, array.size());

        mAnimations.reserve(array.size());

        for(int row = 0; row < array.size(); row++)
        {
            QJsonObject json = array[row].toObject();
            Animation anim;
            anim.fromJSON(json);

            mAnimations.push_back(anim);
            mAssets.push_back(&mAnimations.last());

            if(anim.getUID() > maxUID)
                maxUID = anim.getUID();
        }

        Animation::setCurrentUID(maxUID+1);

        success = true;
        endInsertRows();
    }

    if(json.contains("particles") && json["particles"].isArray())
    {
        unsigned long long maxUID = 0;
        QJsonArray array = json["particles"].toArray();

        beginResetModel();
        mParticles.clear();
        endResetModel();

        beginInsertRows(QModelIndex(), 0, array.size());

        mParticles.reserve(array.size());

        for(int row = 0; row < array.size(); row++)
        {
            QJsonObject json = array[row].toObject();
            Particle part;
            part.fromJSON(json);

            mParticles.push_back(part);
            mAssets.push_back(&mParticles.last());

            if(part.getUID() > maxUID)
                maxUID = part.getUID();
        }

        Particle::setCurrentUID(maxUID+1);

        success = true;
        endInsertRows();
    }

    return success;
}

void AssetModel::writeJSON(unsigned int type, QJsonObject& json)
{
    if(type == Asset::File)
    {
        json.insert("count", QString::number(mFiles.count()));

        QJsonArray fileArray;
        for(auto& Asset : mFiles)
        {
            QJsonObject obj;
            Asset.toJSON(obj);
            fileArray.append(obj);
        }

        json.insert("files", fileArray);
    }

    if(type == Asset::Animation)
    {
        json.insert("count", QString::number(mAnimations.count()));

        QJsonArray fileArray;
        for(auto& Asset : mAnimations)
        {
            QJsonObject obj;
            Asset.toJSON(obj);
            fileArray.append(obj);
        }

        json.insert("animations", fileArray);
    }

    if(type == Asset::Particle)
    {
        json.insert("count", QString::number(mParticles.count()));

        QJsonArray fileArray;
        for(auto& Asset : mParticles)
        {
            QJsonObject obj;
            Asset.toJSON(obj);
            fileArray.append(obj);
        }

        json.insert("particles", fileArray);
    }

}

Asset* AssetModel::getAsset(int row)
{
    if(row >= mAssets.count())
        return nullptr;

    return mAssets[row];
}


File AssetModel::getFile(int row)
{
    if(row >= mFiles.count())
    {
        File Invalid;
        Invalid.setBaseType(Asset::Invalid);
        return Invalid;
    }

    return mFiles[row];
}

Animation AssetModel::getAnimation(int row)
{
    if(row >= mAnimations.count())
    {
        Animation Invalid;
        Invalid.setBaseType(Asset::Invalid);
        return Invalid;
    }

    return mAnimations[row];
}

Particle AssetModel::getParticle(int row)
{
    if(row >= mParticles.count())
    {
        Particle Invalid;
        Invalid.setBaseType(Asset::Invalid);
        return Invalid;
    }

    return mParticles[row];
}

Asset* AssetModel::getByUID(unsigned int type, Asset::UID uid)
{
    for(auto& asset : mAssets)
    {
        if(asset->getUID() == uid)
            if(asset->getBaseType() == type || type == Asset::Invalid)
                return asset;
    }

    return nullptr;
}

void AssetModel::removeAsset(unsigned int type, Asset::UID uid)
{
    int AssetRow = -1;
    int ModelRow = -1;

    for(int i = 0; i < mAssets.count(); i++)
    {
        if(mAssets[i]->getUID() == uid && mAssets[i]->getBaseType() == type)
        {
            AssetRow = i;
            break;
        }
    }

    if(AssetRow == -1)
        return;



    if(type == Asset::File)
    {
        for(int i = 0; i < mFiles.count(); i++)
        {
            if(mFiles[i].getUID() == uid)
            {
                ModelRow = i;
                break;
            }
        }
    }
    if(type == Asset::Animation)
    {
        for(int i = 0; i < mAnimations.count(); i++)
        {
            if(mAnimations[i].getUID() == uid)
            {
                ModelRow = i;
                break;
            }
        }
    }
    if(type == Asset::Particle)
    {
        for(int i = 0; i < mParticles.count(); i++)
        {
            if(mParticles[i].getUID() == uid)
            {
                ModelRow = i;
                break;
            }
        }
    }

    if(ModelRow == -1)
        return;

    if(mType == Asset::Invalid)
        beginRemoveRows(QModelIndex(), AssetRow, AssetRow);
    else
        beginRemoveRows(QModelIndex(), ModelRow, ModelRow);

    if(type == Asset::File)
        mFiles.removeAt(ModelRow);
    if(type == Asset::Animation)
        mAnimations.removeAt(ModelRow);
    if(type == Asset::Particle)
        mParticles.removeAt(ModelRow);

    mAssets.removeAt(AssetRow);
    endRemoveRows();
}

void AssetModel::removeAnimation(Animation::UID uid)
{
    int row = -1;

    for(int i = 0; i < mAnimations.count(); i++)
    {
        if(mAnimations[i].getUID() == uid)
        {
            row = i;
            break;
        }
    }

    if(row == -1)
        return;

    beginRemoveRows(QModelIndex(), row, row);
    mAnimations.removeAt(row);
    endRemoveRows();
}

void AssetModel::removeFile(unsigned long long uid)
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

void AssetModel::removeParticle(Particle::UID uid)
{
    int row = -1;

    for(int i = 0; i < mParticles.count(); i++)
    {
        if(mParticles[i].getUID() == uid)
        {
            row = i;
            break;
        }
    }

    if(row == -1)
        return;

    beginRemoveRows(QModelIndex(), row, row);
    mParticles.removeAt(row);
    endRemoveRows();
}


void AssetModel::addAnimation(Animation anim)
{
    beginInsertRows(QModelIndex(), mAnimations.count(), mAnimations.count());
    mAnimations.insert(mAnimations.count(), anim);
    mAssets.insert(mAssets.count(), &mAnimations.last());
    endInsertRows();
}

void AssetModel::addFile(File file)
{
    beginInsertRows(QModelIndex(), mFiles.count(), mFiles.count());
    mFiles.insert(mFiles.count(), file);
    mAssets.insert(mAssets.count(), &mFiles.last());
    endInsertRows();
}

void AssetModel::addParticle(Particle anim)
{
    beginInsertRows(QModelIndex(), mParticles.count(), mParticles.count());
    mParticles.insert(mParticles.count(), anim);
    mAssets.insert(mAssets.count(), &mParticles.last());
    endInsertRows();
}

unsigned long long AssetModel::getUID(QModelIndex index)
{
    if(!index.isValid())
        return 0;

    if(mType == Asset::Invalid && index.row() < mAssets.count())
        return mAssets[index.row()]->getUID();
    if(mType == Asset::File && index.row() < mFiles.count())
        return mFiles[index.row()].getUID();
    if(mType == Asset::Animation && index.row() < mAnimations.count())
        return mAnimations[index.row()].getUID();
    if(mType == Asset::Particle && index.row() < mParticles.count())
        return mParticles[index.row()].getUID();

    return 0;
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

