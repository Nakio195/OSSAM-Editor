#include "File.h"

File::File(File::Type type, QString name, QString path) : Asset(Asset::File, name), mPath(path), mType(type)
{
}

void File::setPath(QString path)
{
    mPath = path;
}

QString File::getPath() const
{
    return mPath;
}

void File::setType(File::Type type)
{
    mType = type;
}

File::Type File::getType() const
{
    return mType;
}

QString File::TypeToText(File::Type type)
{
    switch(type)
    {
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

File::Type File::TypeFromText(QString text)
{
    if(text == QString("Texture"))
        return File::Texture;
    if(text == QString("Police"))
        return File::Font;
    if(text == QString("Shader"))
        return File::Shader;
    if(text == QString("Son"))
        return File::Sound;

    return File::Invalid;
}

void File::toJSON(QJsonObject& asset) const
{
    asset.insert("uid", QJsonValue(QString::number(mUID)));
    asset.insert("name", QJsonValue(mName));
    asset.insert("path", QJsonValue(mPath));
    asset.insert("type", QJsonValue(File::TypeToText(mType)));

}

void File::fromJSON(const QJsonObject &json)
{
    mUID = json.value("uid").toString().toULongLong();
    mName = json.value("name").toString();
    mPath = json.value("path").toString();
    mType = TypeFromText(json.value("type").toString());
}

