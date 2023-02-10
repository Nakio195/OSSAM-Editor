#include "ParticleManager/ParticleModel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

ParticleModel::ParticleModel(AssetModel *assets, QObject *parent)
    : QAbstractTableModel(parent), mAssets(assets)
{
}

QVariant ParticleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            switch(section)
            {
            case ParticleModel::ID:
                return QVariant(QString("ID"));
            case ParticleModel::Name:
                return QVariant(QString("Nom"));
            case ParticleModel::TextureUID:
                return QVariant(QString("Texture ID"));
            case ParticleModel::LifeTime:
                return QVariant(QString("Temps de vie"));
            case ParticleModel::Color:
                return QVariant(QString("Couleur"));
            }
        }
    }

    return QVariant();
}

int ParticleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return mParticles.count();
    // FIXME: Implement me!
}

int ParticleModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 5;
    // FIXME: Implement me!
}


void ParticleModel::sort(int column, Qt::SortOrder order)
{
    layoutAboutToBeChanged();

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

    layoutChanged();
}

QVariant ParticleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() >= mParticles.count())
        return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch(index.column())
        {
            case ParticleModel::ID:
                return QVariant(QString::number(mParticles[index.row()].getUID()));
            case ParticleModel::Name:
                return QVariant(mParticles[index.row()].getName());
            case ParticleModel::TextureUID:
                return QVariant(mParticles[index.row()].getTextureUID());
            case ParticleModel::LifeTime:
                return QVariant(mParticles[index.row()].getLifeTime());
            case ParticleModel::Color:
                return QVariant(mParticles[index.row()].getColor());
        }
    }

    if(role == Qt::BackgroundRole && index.column() == ParticleModel::Color)
        return QVariant(QBrush(mParticles[index.row()].getColor()));

    return QVariant();
}

bool ParticleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        if(index.row() < mParticles.size())
        {
            switch(index.column())
            {
                case ParticleModel::ID:
                    break;

                case ParticleModel::Name:
                    mParticles[index.row()].setName(value.toString());
                    emit dataChanged(index, index, {role});
                    return true;

                case ParticleModel::LifeTime:
                    mParticles[index.row()].setLifeTime(value.toFloat());
                    emit dataChanged(index, index, {role});
                    return true;

                case ParticleModel::Color:
                    mParticles[index.row()].setColor(QColor(value.toString()));
                    emit dataChanged(index, index, {role});
                    return true;
            }
        }
    }

    return false;
}

Qt::ItemFlags ParticleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if(index.column() == ParticleModel::Name)
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    if(index.column() == ParticleModel::LifeTime)
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    if(index.column() == ParticleModel::Color)
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;

    return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
}

bool ParticleModel::insertRows(int , int , const QModelIndex &)
{
    return false;
}

bool ParticleModel::insertColumns(int , int , const QModelIndex &)
{
    return false;
}


const QVector<Particle>& ParticleModel::getParticles()
{
    return mParticles;
}

bool ParticleModel::readJSON(QJsonObject &json)
{
    if(json.contains("Particles") && json["Particles"].isArray())
    {
        unsigned long long maxUID = 0;
        QJsonArray array = json["Particles"].toArray();

        beginResetModel();
        mParticles.clear();
        endResetModel();

        beginInsertRows(QModelIndex(), 0, array.size());

        mParticles.reserve(array.size());

        for(int row = 0; row < array.size(); row++)
        {
            QJsonObject json = array[row].toObject();
            Particle anim;
            anim.fromJSON(json);

            mParticles.push_back(anim);
            mAssets->addAsset(&mParticles.last());

            if(anim.getUID() > maxUID)
                maxUID = anim.getUID();
        }

        Particle::setCurrentUID(maxUID+1);

        endInsertRows();

        return true;
    }

    return false;
}

void ParticleModel::writeJSON(QJsonObject& json)
{
    json.insert("count", QString::number(mParticles.count()));

    QJsonArray animArray;
    for(auto& particle : mParticles)
    {
        QJsonObject obj;
        particle.toJSON(obj);
        animArray.append(obj);
    }

    json.insert("Particles", animArray);

}

const Particle ParticleModel::getParticle(int row)
{
    if(row >= mParticles.count())
        return Particle();

    return mParticles[row];
}

const Particle ParticleModel::getByUID(Particle::UID uid)
{
    for(auto& anim : mParticles)
    {
        if(anim.getUID() == uid)
            return anim;
    }

    return Particle();
}

void ParticleModel::removeParticle(Particle::UID uid)
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

void ParticleModel::addParticle(Particle anim)
{
    beginInsertRows(QModelIndex(), mParticles.count(), mParticles.count());
    mParticles.insert(mParticles.count(), anim);
    mAssets->addAsset(&mParticles.last());
    endInsertRows();
}

unsigned long long ParticleModel::getUID(QModelIndex index)
{
    if(!index.isValid())
        return 0;

    return mParticles[index.row()].getUID();
}

bool ParticleModel::loadFromFile(QString path)
{
    QFile AnimFile(path);

    if(!AnimFile.open(QIODevice::ReadOnly))
        QMessageBox::critical(nullptr, "Erreur plutôt critique quand même", "Impossible d'accéder au fichier de sauvegarde des Particles : " + path);
    else
    {
        QJsonObject particles(QJsonDocument::fromJson(AnimFile.readAll()).object());
        readJSON(particles);

        return true;
    }
    return false;
}

