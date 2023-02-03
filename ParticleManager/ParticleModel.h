#ifndef PARTICLEMODEL_H
#define PARTICLEMODEL_H

#include <QAbstractTableModel>

class ParticleModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ParticleModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // PARTICLEMODEL_H
