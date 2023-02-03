#ifndef AnimationCreator_H
#define AnimationCreator_H

#include <SFML/Graphics/Texture.hpp>
#include <QDialog>
#include "FileManager/FileModel.h"
#include "AnimationManager/Animation.h"

namespace Ui {
class AnimationCreator;
}

class AnimationCreator : public QDialog
{
    Q_OBJECT

    public:
        explicit AnimationCreator(AssetModel* assets, QWidget *parent = nullptr);
        ~AnimationCreator();

        static Animation create(AssetModel* assets, QWidget *parent);

        Animation getAnimation();

    signals:
        void requestSave();

    private slots:
        void browseFile();
        void parametersEdited();
        void textureChanged(const sf::Texture& texture);

        void setBackgroundColor();

    private:
        Ui::AnimationCreator *ui;
        FileModel* mFiles;
        AssetModel *mAssets;

        File mTexture;
        Animation mAnimation;
};

#endif // AnimationCreator_H
