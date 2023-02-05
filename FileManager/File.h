#ifndef FILE_H
#define FILE_H

#include <QString>
#include "Asset.h"

class File : public Asset
{
    public:
        enum Type
        {
            Texture,
            Sound,
            Shader,
            Font,
            Invalid
        };


        File(File::Type type = Type::Invalid, QString name = "", QString path = "");

        void setPath(QString path);
        QString getPath() const;

        void setType(File::Type type);
        File::Type getType() const;
        static QString TypeToText(File::Type type);
        static File::Type TypeFromText(QString text);


        void toJSON(QJsonObject& asset) const;
        void fromJSON(const QJsonObject &json);

    private:
        QString mPath;
        File::Type mType;
};


#endif // RESSOURCE_H
