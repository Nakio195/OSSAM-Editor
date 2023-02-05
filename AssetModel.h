#ifndef ASSETMODEL_H
#define ASSETMODEL_H

#include <QAbstractTableModel>
#include "Asset.h"

#include "FileManager/File.h"
#include "AnimationManager/Animation.h"
#include "ParticleManager/Particle.h"

class AssetModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        enum AssetColumn{
            ID = 0,
            Name = 1,
            Type = 2
        };

        enum FileColumn{
            Path = 3
        };

        enum AnimationColumn{
            TextureUID = 2,
            FrameCount = 3,
            RectWidth = 4,
            RectHeight = 5,
            Period = 6,
            TimerMode = 7
        };

        enum ParticleColumns{
            LifeTime = 3,
            Color = 4,
        };

    public:
        explicit AssetModel(QObject *parent = nullptr);

        void setType(unsigned int type);

        // Header:
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        // Basic functionality:
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        // Edit functionality
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        Qt::ItemFlags flags(const QModelIndex& index) const override;
        bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
        bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
        void sort(int column, Qt::SortOrder order) override;

        // Assets functions
        const QVector<Asset *> &getAssets();
        unsigned long long getUID(QModelIndex index);

        void removeAsset(unsigned int type, Asset::UID uid);
        void removeFile(unsigned long long uid);
        void removeAnimation(Animation::UID uid);
        void removeParticle(Particle::UID uid);

        void addFile(File file);
        void addAnimation(Animation anim);
        void addParticle(Particle anim);

        Asset* getAsset(int row);
        File getFile(int row);
        Animation getAnimation(int row);
        Particle getParticle(int row);
        Asset* getByUID(unsigned int type, unsigned long long UID);

        //JSON functions
        bool readJSON(QJsonObject& json);
        void writeJSON(unsigned int type, QJsonObject& json);
        bool loadFromFile(QString path);

    private:

        unsigned int mType;
        QVector<Asset*> mAssets;
        QVector<Animation> mAnimations;
        QVector<File> mFiles;
        QVector<Particle> mParticles;
};

#endif // ASSETMODEL_H
