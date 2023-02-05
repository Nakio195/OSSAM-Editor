#ifndef OSSAM_ANIMATIONVIEWER_H
#define OSSAM_ANIMATIONVIEWER_H

#include <SFML/Graphics.hpp>
#include "widgets/QSFMLView.h"
#include "AnimationManager/Animation.h"

class AnimationViewer : public QSFMLView
{
    Q_OBJECT

    public:
        AnimationViewer(QWidget* Parent, const QPoint& Position, const QSize& Size);
        AnimationViewer(QWidget*& Parent);
        AnimationViewer(QDialog*& Parent);

    signals:
        void textureChanged(const sf::Texture& texture);

    public slots:
        void setRect(sf::IntRect rect);
        void setFrames(int frames);
        void setPeriod(float period);
        void setMode(Animation::TimerMode mode);
        void setTexture(QString path);
        void play();

        void setBackgroundColor(QColor color);
        void setAnimation(Animation anim);

    private :
        void onInit() override;
        void onUpdate() override;
        void resizeEvent(QResizeEvent*) override;

    private:
        sf::IntRect mRect;
        int mFrames;
        float mPeriod;
        Animation::TimerMode mMode;

        sf::Texture mTexture;
        sf::Sprite mSprite;
        sf::Sprite mAnimatedSprite;

        sf::RectangleShape mRectSprite;

        bool mPlaying;
        float dt;
        int mCurrentFrame;
};


#endif // OSSAM_ANIMATIONVIEWER_H
