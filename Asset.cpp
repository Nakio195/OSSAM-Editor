#include "Asset.h"

unsigned long long Asset::sUID = 1;

Asset::Asset(Asset::Type type, QString name) :
    mName(name),
    mBaseType(type)
{
    mUID = sUID;
    sUID++;
}

Asset::~Asset()
{

}

Asset::UID Asset::getUID() const
{
    return mUID;
}

void Asset::setBaseType(Asset::Type type)
{
    mBaseType = type;
}

Asset::Type Asset::getBaseType() const
{
    return mBaseType;
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

    return Asset::Invalid;
}

void Asset::setCurrentUID(unsigned long long uid)
{
    sUID = uid;
}
