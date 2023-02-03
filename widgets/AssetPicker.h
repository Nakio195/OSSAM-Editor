#ifndef ASSETPICKER_H
#define ASSETPICKER_H

#include <QDialog>
#include "Asset.h"
#include "AssetModel.h"
#include <QModelIndex>
#include <QSortFilterProxyModel>

namespace Ui {
class Dialog;
}

class AssetPicker : public QDialog
{
    Q_OBJECT

    public:
        explicit AssetPicker(AssetModel* assets, QWidget *parent = nullptr, Asset::Type type = Asset::Invalid);
        ~AssetPicker();

        static Asset pick(AssetModel* assets, QWidget *parent = nullptr, Asset::Type type = Asset::Invalid);

    private slots:
        void selectionChanged(const QModelIndex&, const QModelIndex& column);
        void search(QString string);

    private:
        Asset selectedAsset();

    private:
        Ui::Dialog *ui;

        AssetModel* mAssets;
        QSortFilterProxyModel mFilter;
        QSortFilterProxyModel mSearch;

        bool mFiltered;
        bool mSearched;
};

#endif // ASSETPICKER_H
