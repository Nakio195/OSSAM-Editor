#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <QWidget>

namespace Ui {
class AssetManager;
}

class AssetManager : public QWidget
{
    Q_OBJECT

public:
    explicit AssetManager(QWidget *parent = nullptr);
    ~AssetManager();

private:
    Ui::AssetManager *ui;
};

#endif // ASSETMANAGER_H
