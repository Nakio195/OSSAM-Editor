#ifndef ASSETMODEL_H
#define ASSETMODEL_H

#include <QAbstractTableModel>
#include "Asset.h"

class AssetModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        enum Columns{
            ID = 0,
            Name = 1,
            Type = 2
        };

    public:
        explicit AssetModel(QObject *parent = nullptr);

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
        void removeAsset(Asset::UID uid);
        void addAsset(Asset *asset);
        Asset* getAsset(int row);
        Asset* getByUID(unsigned long long UID);

    private:
        QVector<Asset*> mAssets;
};

#endif // ASSETMODEL_H
