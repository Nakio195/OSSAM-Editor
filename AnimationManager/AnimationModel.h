#ifndef ANIMATIONMODEL_H
#define ANIMATIONMODEL_H

#include <QAbstractTableModel>
#include "AnimationManager/Animation.h"

class AnimationModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        enum Columns{
            ID = 0,
            Name = 1,
            TextureUID = 2,
            FrameCount = 3,
            RectWidth = 4,
            RectHeight = 5,
            Period = 6,
            TimerMode = 7
        };

    public:
        explicit AnimationModel(QObject *parent = nullptr);

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

        // Animations functions
        const QVector<Animation>& getAnimations();
        unsigned long long getUID(QModelIndex index);
        void removeAnimation(Animation::UID uid);
        void addAnimation(Animation animation);
        const Animation getAnimation(int row);
        const Animation getByUID(unsigned long long UID);

        //JSON functions
        bool readJSON(QJsonObject& json);
        void writeJSON(QJsonObject& json);
        bool loadFromFile(QString path);

    private:
        QVector<Animation> mAnimations;

};

#endif // ANIMATIONMODEL_H
