#include "File.h"

File::File(File::Type type, QString name, QString path) : Asset(type, name), mPath(path)
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

