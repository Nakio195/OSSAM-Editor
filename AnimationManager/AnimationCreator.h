#ifndef AnimationCreator_H
#define AnimationCreator_H

#include <SFML/Graphics/Texture.hpp>
#include <QDialog>
#include "Context.h"

namespace Ui {
class AnimationCreator;
}

class AnimationCreator : public QDialog
{
    Q_OBJECT

    public:
        explicit AnimationCreator(Context* context, QWidget *parent = nullptr);
        ~AnimationCreator();

        static Animation create(Context* context, QWidget *parent);

        Animation getAnimation();

    signals:
        void requestSave();

    private slots:
        void browseFiles();
        void parametersEdited();
        void textureChanged(const sf::Texture& texture);

        void setBackgroundColor();

    private:
        Ui::AnimationCreator *ui;

        Context *mContext;

        File mTexture;
        Animation mAnimation;
};

#endif // AnimationCreator_H
