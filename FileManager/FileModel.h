#ifndef FileMODEL_H
#define FileMODEL_H

#include <QAbstractTableModel>

#include "AssetModel.h"
#include "FileManager/File.h"

class FileModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        explicit FileModel(AssetModel* assets, QObject *parent = nullptr);

        enum Columns{
            ID = 0,
            Name = 1,
            Type = 2,
            Path = 3
        };

        // Header:
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        // Basic functionality:
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

        // Edit functionality
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

        // File functions
        const QVector<File>& getFiles();
        unsigned long long getUID(QModelIndex index);
        void removeFile(unsigned long long uid);
        void addFile(File file);
        const File getFile(int row);
        const File getByUID(unsigned long long UID);

        //JSON functions
        bool readJSON(QJsonObject& json);
        void writeJSON(QJsonObject& json);
        bool loadFromFile(QString path);


    private:
        AssetModel *mAssets;
        QVector<File> mFiles;
};

#endif // FileMODEL_H
