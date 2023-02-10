#ifndef FILE_H
#define FILE_H

#include <QString>
#include "Asset.h"

class File : public Asset
{
    public:

        File(Asset::Type type = Type::Invalid, QString name = "", QString path = "");

        void setPath(QString path);
        QString getPath() const;

        void toJSON(QJsonObject& asset) const;
        void fromJSON(const QJsonObject &json);

    private:
        QString mPath;
};


#endif // RESSOURCE_H
