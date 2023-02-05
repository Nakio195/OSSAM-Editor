#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QSortFilterProxyModel>
#include "AssetModel.h"

namespace Ui {
class AnimationManager;
}

class AnimationManager : public QWidget
{
    Q_OBJECT

    public:
        explicit AnimationManager(AssetModel* assets,  QWidget *parent = nullptr);
        ~AnimationManager() override;

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
        Ui::AnimationManager *ui;

        AssetModel* mAssets;

        QSortFilterProxyModel mSearchProxy;
};

#endif // ANIMATIONMANAGER_H
