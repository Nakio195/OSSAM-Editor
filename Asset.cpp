#include "Asset.h"

unsigned long long Asset::sUID = 1;

Asset::Asset(Asset::Type type, QString name) :
    mName(name),
    mType(type)
{
    if(type != Invalid)
    {
        mID = sUID;
        sUID++;
    }
}

Asset::UID Asset::getUID() const
{
    return mID;
}

void Asset::setType(Asset::Type type)
{
    mType = type;
}

Asset::Type Asset::getType() const
{
    return mType;
}

void Asset::setName(QString name)
{
    mName = name;
}

QString Asset::getName() const
{
    return mName;
}

QString Asset::TypeToText(Asset::Type type)
{
    switch(type)
    {
        case Texture:
            return QString("Texture");
        case Font:
            return QString("Police");
        case Shader:
            return QString("Shader");
        case Sound:
            return QString("Son");

        case Invalid:
        default:
            return QString("Invalide");
    }
}

Asset::Type Asset::TypeFromText(QString text)
{
    if(text == QString("Texture"))
        return Asset::Texture;
    if(text == QString("Police"))
        return Asset::Font;
    if(text == QString("Shader"))
        return Asset::Shader;
    if(text == QString("Son"))
        return Asset::Sound;

    return Asset::Invalid;
}

void Asset::toJSON(QJsonObject& asset) const
{
    asset.insert("uid", QJsonValue(QString::number(mID)));
    asset.insert("name", QJsonValue(mName));
    asset.insert("type", QJsonValue(TypeToText(mType)));
}

void Asset::fromJSON(const QJsonObject &json)
{
    mID = json.value("uid").toString().toULongLong();
    mName = json.value("name").toString();
    mType = TypeFromText(json.value("type").toString());
}


void Asset::setCurrentUID(unsigned long long uid)
{
    sUID = uid;
}
