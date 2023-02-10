#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QDataWidgetMapper>
#include <QMediaPlayer>
#include <QSound>
#include <QSortFilterProxyModel>

#include "FileManager/File.h"
#include "Context.h"


namespace Ui{
    class FileManager;
}

class FileManager : public QWidget
{
    Q_OBJECT

    public:
        explicit FileManager(Context *context, QWidget *parent = nullptr);
        ~FileManager();

        const File getByUID(unsigned long long UID);

    signals:
        void requestSave();

    public slots:
        bool saveToFile();
        void focusChange(QMdiSubWindow* window);

    private slots:
        void selectionChanged(const QModelIndex &current,const QModelIndex &previous);
        void rowChanged(QModelIndex index);
        void createFile();
        void removeFile();
        void browseForFile();
        void saveChanges();


        void search(QString string);

    private:
        void addAsset(const Asset& asset);
        void updateViewer();

        QString browse();

        void closeEvent(QCloseEvent *event) override;

    private:
        Ui::FileManager *ui;
        QDataWidgetMapper mMapper;

        unsigned long long mCurrentUID;

        Context* mContext;
        QSortFilterProxyModel mSearchProxy;

        bool mPendingChanges;
};

#endif // ASSETMANAGER_H
