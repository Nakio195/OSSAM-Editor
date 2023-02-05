#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QSortFilterProxyModel>
#include "AssetModel.h"

namespace Ui {
class ParticleManager;
}

class ParticleManager : public QWidget
{
    Q_OBJECT

    public:
        explicit ParticleManager(AssetModel* assets, QWidget *parent = nullptr);
        ~ParticleManager() override;

    public slots:
        void search(QString string);
        void create();
        void remove();
        void save();

        void focusChange(QMdiSubWindow* window);

        void selectionChanged(const QModelIndex &current, const QModelIndex &);

    signals:
        void requestSave();

    private:
        void closeEvent(QCloseEvent *event) override;

    private:
        Ui::ParticleManager *ui;

        AssetModel* mAssets;

        QSortFilterProxyModel mSearchProxy;

};

#endif // PARTICLEMANAGER_H
