#include "AnimationModel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

AnimationModel::AnimationModel(AssetModel *assets, QObject *parent)
    : QAbstractTableModel(parent), mAssets(assets)
{
}

QVariant AnimationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            switch(section)
            {
            case AnimationModel::ID:
                return QVariant(QString("ID"));
            case AnimationModel::Name:
                return QVariant(QString("Nom"));
            case AnimationModel::TextureUID:
                return QVariant(QString("Texture ID"));
            case AnimationModel::FrameCount:
                return QVariant(QString("Images"));
            case AnimationModel::RectWidth:
                return QVariant(QString("Largeur"));
            case AnimationModel::RectHeight:
                return QVariant(QString("Hauteur"));
            case AnimationModel::Period:
                return QVariant(QString("Periode"));
            case AnimationModel::TimerMode:
                return QVariant(QString("Timer Mode"));
            }
        }
    }

    return QVariant();
}

int AnimationModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return mAnimations.count();
    // FIXME: Implement me!
}

int AnimationModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 8;
    // FIXME: Implement me!
}


void AnimationModel::sort(int column, Qt::SortOrder order)
{
    layoutAboutToBeChanged();

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

    layoutChanged();
}

QVariant AnimationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() >= mAnimations.count())
        return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch(index.column())
        {
            case AnimationModel::ID:
                return QVariant(QString::number(mAnimations[index.row()].getUID()));
            case AnimationModel::Name:
                return QVariant(mAnimations[index.row()].getName());
            case AnimationModel::TextureUID:
                return QVariant(mAnimations[index.row()].getTextureUID());
            case AnimationModel::FrameCount:
                return QVariant(mAnimations[index.row()].getFrames());
            case AnimationModel::RectWidth:
                return QVariant(mAnimations[index.row()].getWidth());
            case AnimationModel::RectHeight:
                return QVariant(mAnimations[index.row()].getHeight());
            case AnimationModel::Period:
                return QVariant(mAnimations[index.row()].getPeriod());
            case AnimationModel::TimerMode:
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

    if(role == Qt::BackgroundRole)
        return index.row() % 2 ? QVariant(QBrush(QColor(0, 140, 255))) : QVariant(QBrush(QColor(100, 180, 255)));

    return QVariant();
}

bool AnimationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        if(index.row() < mAnimations.size())
        {
            switch(index.column())
            {
                case AnimationModel::ID:
                    break;

                case AnimationModel::Name:
                    mAnimations[index.row()].setName(value.toString());
                    emit dataChanged(index, index, {role});
                    return true;
            }
        }
    }

    return false;
}

Qt::ItemFlags AnimationModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
}

bool AnimationModel::insertRows(int , int , const QModelIndex &)
{
    return false;
}

bool AnimationModel::insertColumns(int , int , const QModelIndex &)
{
    return false;
}


const QVector<Animation>& AnimationModel::getAnimations()
{
    return mAnimations;
}

bool AnimationModel::readJSON(QJsonObject &json)
{
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
            mAssets->addAsset(&mAnimations.last());

            if(anim.getUID() > maxUID)
                maxUID = anim.getUID();
        }

        Animation::setCurrentUID(maxUID+1);

        endInsertRows();

        return true;
    }

    return false;
}

void AnimationModel::writeJSON(QJsonObject& json)
{
    json.insert("count", QString::number(mAnimations.count()));

    QJsonArray animArray;
    for(auto& anim : mAnimations)
    {
        QJsonObject obj;
        anim.toJSON(obj);
        animArray.append(obj);
    }

    json.insert("animations", animArray);

}

const Animation AnimationModel::getAnimation(int row)
{
    if(row >= mAnimations.count())
        return Animation();

    return mAnimations[row];
}

const Animation AnimationModel::getByUID(Animation::UID uid)
{
    for(auto& anim : mAnimations)
    {
        if(anim.getUID() == uid)
            return anim;
    }

    return Animation();
}

void AnimationModel::removeAnimation(Animation::UID uid)
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

void AnimationModel::addAnimation(Animation anim)
{
    beginInsertRows(QModelIndex(), mAnimations.count(), mAnimations.count());
    mAnimations.insert(mAnimations.count(), anim);
    mAssets->addAsset(&mAnimations.last());
    endInsertRows();
}

unsigned long long AnimationModel::getUID(QModelIndex index)
{
    if(!index.isValid())
        return 0;

    return mAnimations[index.row()].getUID();
}

bool AnimationModel::loadFromFile(QString path)
{
    QFile AnimFile(path);

    if(!AnimFile.open(QIODevice::ReadOnly))
        QMessageBox::critical(nullptr, "Erreur plutôt critique quand même", "Impossible d'accéder au fichier de sauvegarde des Animations : " + path);
    else
    {
        QJsonObject anims(QJsonDocument::fromJson(AnimFile.readAll()).object());
        readJSON(anims);

        return true;
    }
    return false;
}

