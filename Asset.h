#ifndef ASSET_H
#define ASSET_H

#include <QString>
#include <QJsonObject>

class Asset
{
    public:
        typedef unsigned long long UID;

        enum Type{
            Invalid,
            Animation,
            File,
            Particle,
            Texture,
            Sound,
            Shader,
            Font,
            TypeCount
        };

    public:
        Asset(Asset::Type type = Asset::Invalid, QString name = "");
        virtual ~Asset();

        UID getUID() const;
        static void setCurrentUID(unsigned long long uid);

        void setType(Asset::Type type);
        Asset::Type getType() const;

        void setName(QString name);
        QString getName() const;

    public:
        static QString TypeToText(Asset::Type type);
        static Asset::Type TypeFromText(QString text);

    protected:
        static UID sUID;

        QString mName;
        unsigned long long mUID;
        Asset::Type mType;
};

#endif // ASSET_H
