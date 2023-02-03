#ifndef SFML_VIEW_H
#define SFML_VIEW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <QWidget>
#include <QColor>
#include <QTimer>

class QSFMLView : public QWidget, public sf::RenderWindow
{
    public :
        QSFMLView(QWidget* Parent, const QPoint& Position, const QSize& Size, int FrameTime = 5);
        virtual ~QSFMLView();

        float getFrameTime();

    protected:
        void resizeTo(sf::Vector2u size);

    protected:
        sf::View mView;
        QColor mBackColor;

    private :
        virtual void onInit() = 0;
        virtual void onUpdate() = 0;
        virtual QPaintEngine* paintEngine() const;
        virtual void showEvent(QShowEvent*);
        virtual void paintEvent(QPaintEvent*);
        void mouseDoubleClickEvent(QMouseEvent *event);

        void resizeEvent(QResizeEvent* event);

        QTimer mTimer;
        bool   mInitialized;
};

#endif // SFML_VIEW_H
