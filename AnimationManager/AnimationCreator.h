#ifndef ANIMATIONCREATOR_H
#define ANIMATIONCREATOR_H

#include <QDialog>

namespace Ui {
class AnimationCreator;
}

class AnimationCreator : public QDialog
{
    Q_OBJECT

public:
    explicit AnimationCreator(QWidget *parent = nullptr);
    ~AnimationCreator();

private:
    Ui::AnimationCreator *ui;
};

#endif // ANIMATIONCREATOR_H
