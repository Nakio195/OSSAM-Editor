#ifndef ASSETPICKER_H
#define ASSETPICKER_H

#include <QWidget>

namespace Ui {
class AssetPicker;
}

class AssetPicker : public QWidget
{
    Q_OBJECT

public:
    explicit AssetPicker(QWidget *parent = nullptr);
    ~AssetPicker();

private:
    Ui::AssetPicker *ui;
};

#endif // ASSETPICKER_H
