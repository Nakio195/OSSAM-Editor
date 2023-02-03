#ifndef SPACESHIPDATA_H
#define SPACESHIPDATA_H

#include <QWidget>

namespace Ui {
class SpaceshipData;
}

class SpaceshipData : public QWidget
{
    Q_OBJECT

public:
    explicit SpaceshipData(QWidget *parent = nullptr);
    ~SpaceshipData();

private:
    Ui::SpaceshipData *ui;
};

#endif // SPACESHIPDATA_H
