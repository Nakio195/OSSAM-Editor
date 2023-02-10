#include "Asset.h"

unsigned long long Asset::sUID = 1;

Asset::Asset(Asset::Type type, QString name) :
    mName(name),
    mType(type)
{
    if(mType != Asset::Invalid)
    {
        mUID = sUID;
        sUID++;
    }
}

Asset::~Asset()
{

}

Asset::UID Asset::getUID() const
{
    return mUID;
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
        case Invalid:
            return QString("Asset");
        case File:
            return QString("Fichier");
        case Animation:
            return QString("Animation");
        case Particle:
            return QString("Particule");
        case Texture:
            return QString("Texture");
        case Sound:
            return QString("Son");
        case Shader:
            return QString("Shader");
        case Font:
            return QString("Police");

        default:
            return QString("Invalide");
    }
}

Asset::Type Asset::TypeFromText(QString text)
{
    if(text == QString("File"))
        return Asset::File;
    if(text == QString("Animation"))
        return Asset::Animation;
    if(text == QString("Particle"))
        return Asset::Particle;
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

void Asset::setCurrentUID(unsigned long long uid)
{
    sUID = uid;
}
