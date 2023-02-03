#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include <QWidget>

namespace Ui {
class EntityData;
}

class EntityData : public QWidget
{
    Q_OBJECT

public:
    explicit EntityData(QWidget *parent = nullptr);
    ~EntityData();

private:
    Ui::EntityData *ui;
};

#endif // ENTITYDATA_H
