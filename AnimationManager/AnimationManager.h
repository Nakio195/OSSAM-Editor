#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <QWidget>

namespace Ui {
class AnimationManager;
}

class AnimationManager : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationManager(QWidget *parent = nullptr);
    ~AnimationManager();

private:
    Ui::AnimationManager *ui;
};

#endif // ANIMATIONMANAGER_H
