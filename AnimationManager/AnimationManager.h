#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include "Context.h"
#include "FileManager/FileModel.h"
#include "AnimationManager/AnimationModel.h"

namespace Ui {
class AnimationManager;
}

class AnimationManager : public QWidget
{
    Q_OBJECT

    public:
        explicit AnimationManager(Context* context, QWidget *parent = nullptr);
        ~AnimationManager() override;

    public slots:
        void search(QString string);
        void create();
        void remove();
        void save();

        void selectionChanged(const QModelIndex &current, const QModelIndex &);

    signals:
        void requestSave();

    private:
        void closeEvent(QCloseEvent *event) override;

    private:
        Ui::AnimationManager *ui;

        Context* mContext;

        QSortFilterProxyModel mSearchProxy;
};

#endif // ANIMATIONMANAGER_H
