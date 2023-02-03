#ifndef ANIMATION_EDITOR_H
#define ANIMATION_EDITOR_H

#include <QWidget>

namespace Ui {
class Animation_Editor;
}

class Animation_Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Animation_Editor(QWidget *parent = nullptr);
    ~Animation_Editor();

private:
    Ui::Animation_Editor *ui;
};

#endif // ANIMATION_EDITOR_H
