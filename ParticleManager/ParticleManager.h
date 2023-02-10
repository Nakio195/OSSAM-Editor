#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include "Context.h"

namespace Ui {
class ParticleManager;
}

class ParticleManager : public QWidget
{
    Q_OBJECT

    public:
        explicit ParticleManager(Context *context,  QWidget *parent = nullptr);
        ~ParticleManager() override;

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
        Ui::ParticleManager *ui;

        Context* mContext;

        QSortFilterProxyModel mSearchProxy;

};

#endif // PARTICLEMANAGER_H
