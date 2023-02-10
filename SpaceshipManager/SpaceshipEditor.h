#ifndef SPACESHIPEDITOR_H
#define SPACESHIPEDITOR_H

#include <QWidget>

namespace Ui
{
    class SpaceshipEditor;
}

class SpaceshipEditor : public QWidget
{
        Q_OBJECT

    public:
        explicit SpaceshipEditor(QWidget *parent = nullptr);
        ~SpaceshipEditor();

    private:
        Ui::SpaceshipEditor *ui;

//        std::vector<SpaceShipData> mSpaceships;
};

#endif // SPACESHIPEDITOR_H
