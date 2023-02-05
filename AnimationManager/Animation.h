#ifndef ANIMATION_H
#define ANIMATION_H

#include <QString>
#include <QJsonObject>
#include "Asset.h"

class Animation : public Asset
{
    public:
        enum TimerMode{OneShot, Continous};

    public:
        Animation(QString name = "");

        void setTextureUID(UID uid);
        void setFrames(unsigned int frames);
        void setWidth(unsigned int width);
        void setHeight(unsigned int height);
        void setPeriod(float period);
        void setMode(TimerMode mode);

        Asset::UID getTextureUID() const;
        unsigned int getFrames() const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;
        float getPeriod() const;
        TimerMode getMode() const;

    public:
        void toJSON(QJsonObject& Animation) const;
        void fromJSON(const QJsonObject& json);

    private:

        Asset::UID mTexture;
        unsigned int mFrames;
        unsigned int mWidth;
        unsigned int mHeight;
        float mPeriod;
        TimerMode mMode;
};

#endif // ANIMATION_H
