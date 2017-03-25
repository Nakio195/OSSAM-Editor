#ifndef SPACESHIPEDITOR_H
#define SPACESHIPEDITOR_H

#include <QWidget>

namespace Ui {
class SpaceshipEditor;
}

class SpaceshipEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SpaceshipEditor(QWidget *parent = 0);
    ~SpaceshipEditor();

private:
    Ui::SpaceshipEditor *ui;
};

#endif // SPACESHIPEDITOR_H
