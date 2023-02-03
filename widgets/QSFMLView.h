#ifndef SFML_VIEW_H
#define SFML_VIEW_H

#include <QObject>
#include <QWidget>

class SFML_View : public QWidget
{
    Q_OBJECT
public:
    explicit SFML_View(QWidget *parent = nullptr);

signals:

};

#endif // SFML_VIEW_H
