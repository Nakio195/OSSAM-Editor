#ifndef ASSETPICKER_H
#define ASSETPICKER_H

#include <QDialog>
#include <QModelIndex>
#include <QSortFilterProxyModel>

#include "Context.h"

namespace Ui {
class Dialog;
}

class AssetPicker : public QDialog
{
    Q_OBJECT

    public:
        explicit AssetPicker(Context* context, QWidget *parent = nullptr, Asset::Type type = Asset::Invalid);
        ~AssetPicker();

        static Asset::UID pick(Context* context, QWidget *parent = nullptr, Asset::Type type = Asset::Invalid);

    private slots:
        void selectionChanged(const QModelIndex&, const QModelIndex& column);
        void search(QString string);

    private:
        Asset::UID selectedAsset();

    private:
        Ui::Dialog *ui;

        QAbstractItemModel* mSourceModel;
        Context* mContext;
        Asset::Type mType;

        QSortFilterProxyModel mFilter;
        QSortFilterProxyModel mSearch;

        bool mFiltered;
        bool mSearched;
};

#endif // ASSETPICKER_H
