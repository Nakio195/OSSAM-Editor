#include "Animation.h"

Animation::Animation(QString name) : Asset(Asset::Animation, name)
{
    if(name == QString(""))
        mName = QString("Invalid");

    mTexture = 0;
    mFrames = 1;
    mWidth = 20;
    mHeight = 20;
    mPeriod = 0.02f;
    mMode = TimerMode::OneShot;
}

void Animation::setTextureUID(UID uid)
{
    mTexture = uid;
}

void Animation::setFrames(unsigned int frames)
{
    mFrames = frames;
}

void Animation::setWidth(unsigned int width)
{
    mWidth = width;
}

void Animation::setHeight(unsigned int height)
{
    mHeight = height;
}

void Animation::setPeriod(float period)
{
    mPeriod = period;
}

void Animation::setMode(TimerMode mode)
{
    mMode = mode;
}

Asset::UID Animation::getTextureUID() const
{
    return mTexture;
}

unsigned int Animation::getFrames() const
{
    return mFrames;
}

unsigned int Animation::getWidth() const
{
    return mWidth;
}

unsigned int Animation::getHeight() const
{
    return mHeight;
}

float Animation::getPeriod() const
{
    return mPeriod;
}

Animation::TimerMode Animation::getMode() const
{
    return mMode;
}

void Animation::toJSON(QJsonObject& anim) const
{
    anim.insert("uid", QJsonValue(QString::number(mUID)));
    anim.insert("name", QJsonValue(mName));
    anim.insert("texture", QJsonValue(QString::number(mTexture)));
    anim.insert("frames", QJsonValue(static_cast<int>(mFrames)));
    anim.insert("width", QJsonValue(static_cast<int>(mWidth)));
    anim.insert("height", QJsonValue(static_cast<int>(mHeight)));
    anim.insert("period", QJsonValue(static_cast<double>(mPeriod)));
    anim.insert("mode", QJsonValue(static_cast<int>(mMode)));
}

void Animation::fromJSON(const QJsonObject& json)
{
    mUID = json.value("uid").toString().toULongLong();
    mName = json.value("name").toString();
    mTexture = json.value("texture").toString().toULongLong();
    mFrames = static_cast<unsigned int>(json.value("frames").toInt());
    mWidth = static_cast<unsigned int>(json.value("width").toInt());
    mHeight = static_cast<unsigned int>(json.value("height").toInt());
    mPeriod = static_cast<float>(json.value("period").toDouble());
    mMode = TimerMode(json.value("mode").toInt());
}
