#ifndef PARTICLEMODEL_H
#define PARTICLEMODEL_H

#include <QAbstractTableModel>
#include "ParticleManager/Particle.h"

class ParticleModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        enum Columns{
            ID = 0,
            Name = 1,
            TextureUID = 2,
            LifeTime = 3,
            Color = 4,
        };

    public:
        explicit ParticleModel(QObject *parent = nullptr);

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

        // Particles functions
        const QVector<Particle>& getParticles();
        unsigned long long getUID(QModelIndex index);
        void removeParticle(Particle::UID uid);
        void addParticle(Particle Particle);
        const Particle getParticle(int row);
        const Particle getByUID(unsigned long long UID);

        //JSON functions
        bool readJSON(QJsonObject& json);
        void writeJSON(QJsonObject& json);
        bool loadFromFile(QString path);

    private:
        QVector<Particle> mParticles;
};

#endif // PARTICLEMODEL_H
