#include "Particle.h"


Particle::Particle() : Asset(Asset::Particle)
{
    mLifeTime = 0.1f;
    mTexture = 0;
    mColor.setRgb(0, 0, 0);
}


QString Particle::getName() const
{
    return mName;
}

QColor Particle::getColor() const
{
    return mColor;
}

float Particle::getLifeTime() const
{
    return mLifeTime;
}

File::UID Particle::getTextureUID() const
{
    return mTexture;
}

void Particle::setName(QString name)
{
    mName = name;
}

void Particle::setColor(QColor color)
{
    mColor = color;
}

void Particle::setLifeTime(float time)
{
    if(time > 0.f)
        mLifeTime = time;
}

void Particle::setTextureUID(Asset::UID uid)
{
    mTexture = uid;
}

void Particle::toJSON(QJsonObject& Particle) const
{
    Particle.insert("uid", QJsonValue(QString::number(mUID)));
    Particle.insert("name", QJsonValue(mName));
    Particle.insert("texture", QJsonValue(QString::number(mTexture)));
    Particle.insert("lifetime", QJsonValue(static_cast<double>(mLifeTime)));
    Particle.insert("r", QJsonValue(static_cast<int>(mColor.red())));
    Particle.insert("g", QJsonValue(static_cast<int>(mColor.green())));
    Particle.insert("b", QJsonValue(static_cast<int>(mColor.blue())));
}

void Particle::fromJSON(const QJsonObject& json)
{
    mUID = json.value("uid").toString().toULongLong();
    mName = json.value("name").toString();
    mTexture = json.value("texture").toString().toULongLong();
    mLifeTime = static_cast<float>(json.value("lifetime").toDouble());
    mColor.setRed(json.value("r").toInt());
    mColor.setGreen(json.value("g").toInt());
    mColor.setBlue(json.value("b").toInt());
}

