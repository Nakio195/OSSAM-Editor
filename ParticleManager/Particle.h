#ifndef PARTICLE_H
#define PARTICLE_H

#include <QColor>
#include "Asset.h"
#include "FileManager/File.h"

class Particle : Asset
{
    public:
        typedef unsigned long long UID;

    public:
        Particle();

        UID getUID() const;
        QString getName() const;
        QColor getColor() const;
        float getLifeTime() const;
        File::UID getTextureUID() const;

        void setName(QString name);
        void setColor(QColor color);
        void setLifeTime(float time);
        void setTextureUID(File::UID uid);

        static void setCurrentUID(UID uid);

    public:
        void toJSON(QJsonObject& Particle) const;
        void fromJSON(const QJsonObject& json);

    private:
        UID mUID;
        QString mName;
        float mLifeTime;
        QColor mColor;
        File::UID mTexture;

        static UID sUID;
};

#endif // PARTICLE_H
