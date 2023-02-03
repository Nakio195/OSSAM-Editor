#ifndef ASSETVIEWER_H
#define ASSETVIEWER_H

#include <QWidget>

namespace Ui {
class AssetViewer;
}

class AssetViewer : public QWidget
{
    Q_OBJECT

public:
    explicit AssetViewer(QWidget *parent = nullptr);
    ~AssetViewer();

private:
    Ui::AssetViewer *ui;
};

#endif // ASSETVIEWER_H
