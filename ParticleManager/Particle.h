#ifndef PARTICLE_H
#define PARTICLE_H

#include <QColor>
#include "Asset.h"
#include "FileManager/File.h"

class Particle : public Asset
{
    public:
        Particle();

        QString getName() const;
        QColor getColor() const;
        float getLifeTime() const;
        Asset::UID getTextureUID() const;

        void setName(QString name);
        void setColor(QColor color);
        void setLifeTime(float time);
        void setTextureUID(Asset::UID uid);

    public:
        void toJSON(QJsonObject& Particle) const;
        void fromJSON(const QJsonObject& json);

    private:
        QString mName;
        float mLifeTime;
        QColor mColor;
        Asset::UID mTexture;

};

#endif // PARTICLE_H
