#include "AnimationViewer.h"
#include <QMessageBox>


AnimationViewer::AnimationViewer(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLView(Parent, Position, Size)
{
    mFrames = 1;
    mRect = sf::IntRect();
    mPeriod = 500.f;
    mPlaying = false;
    mCurrentFrame = 0;
    mMode = Animation::OneShot;

    mView.setCenter(0, 0);
}

AnimationViewer::AnimationViewer(QWidget*& Parent) : AnimationViewer(Parent, Parent->pos(), Parent->size())
{
}

AnimationViewer::AnimationViewer(QDialog*& Parent) : AnimationViewer(Parent, Parent->pos(), Parent->size())
{
}


void AnimationViewer::onInit()
{

}

void AnimationViewer::setAnimation(Animation anim)
{
    setRect(sf::IntRect(0, 0, static_cast<int>(anim.getWidth()), static_cast<int>(anim.getHeight())));
    setFrames(static_cast<int>(anim.getFrames()));
    setPeriod(anim.getPeriod());
    setMode(Animation::Continous);
}

void AnimationViewer::setBackgroundColor(QColor color)
{
    mBackColor = color;
}

void AnimationViewer::onUpdate()
{
    sf::IntRect rect = mRect;

    if(mPlaying)
        dt += getFrameTime();

    if(dt >= mPeriod)
    {
        dt -= mPeriod;
        mCurrentFrame = (mCurrentFrame+1);

        if(mCurrentFrame == mFrames)
        {
            mCurrentFrame = 0;

            if(mMode == Animation::OneShot)
                mPlaying = false;
        }

        rect.left = mCurrentFrame*mRect.width;
        mAnimatedSprite.setTextureRect(rect);
    }

    clear(sf::Color(mBackColor.red(), mBackColor.green(),mBackColor.blue()));
    setView(mView);
    draw(mAnimatedSprite);
}

void AnimationViewer::play()
{
    mPlaying = mPlaying ? false : true;
}

void AnimationViewer::setMode(Animation::TimerMode mode)
{
    mMode = mode;
}

void AnimationViewer::setRect(sf::IntRect rect)
{
    mRect = rect;
    mAnimatedSprite.setTextureRect(mRect);
    mAnimatedSprite.setOrigin(sf::Vector2f(mRect.width/2, mRect.height/2));
    resizeTo(sf::Vector2u(mRect.width, mRect.height));
    setMaximumSize(mRect.width, mRect.height);
    setMinimumSize(mRect.width, mRect.height);
}

void AnimationViewer::setFrames(int frames)
{
    if(frames > 0)
        mFrames = frames;

    mCurrentFrame = 0;
}

void AnimationViewer::setPeriod(float period)
{
    mPeriod = period*1000;
}


void AnimationViewer::resizeEvent(QResizeEvent*)
{
    sf::Vector2f size(static_cast<float>(mRect.width), static_cast<float>(mRect.height));
    sf::Vector2u sizeu(static_cast<unsigned int>(mRect.width), static_cast<unsigned int>(mRect.height));

    setSize(sizeu);
    mView.setSize(size);
    setView(mView);
}

void AnimationViewer::setTexture(QString path)
{
    if(!mTexture.loadFromFile(path.toStdString()))
        QMessageBox::critical(this, "Ressource indisponible", "Impossible de charger la texture : " + path);

    else
    {
        mRect.width = static_cast<int>(mTexture.getSize().x);
        mRect.height = static_cast<int>(mTexture.getSize().y);
        setRect(mRect);

        mAnimatedSprite.setTexture(mTexture);
        mAnimatedSprite.setTextureRect(mRect);
        mAnimatedSprite.setOrigin(sf::Vector2f(mRect.width/2, mRect.height/2));
        mAnimatedSprite.setPosition(0, 0);

        emit textureChanged(mTexture);
    }
}



