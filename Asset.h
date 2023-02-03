#ifndef ASSET_H
#define ASSET_H

#include <QString>
#include <QJsonObject>

class Asset
{
    public:
        typedef unsigned long long UID;

        enum Type{
            Texture,
            Sound,
            Shader,
            Font,
            Invalid,
            TypeCount
        };

    public:
        Asset(Asset::Type type = Asset::Invalid, QString name = "");
        virtual ~Asset();

        UID getUID() const;

        void setType(Asset::Type type);
        Asset::Type getType() const;

        void setName(QString name);
        QString getName() const;

    public:
        static void setCurrentUID(unsigned long long uid);
        static QString TypeToText(Asset::Type type);
        static Asset::Type TypeFromText(QString text);

        virtual void fromJSON(const QJsonObject& json);
        virtual void toJSON(QJsonObject& asset) const;

    private:
        static UID sUID;

        QString mName;
        unsigned long long mID;
        Asset::Type mType;
};

#endif // ASSET_H
