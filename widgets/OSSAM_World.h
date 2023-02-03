#ifndef WORLD_H
#define WORLD_H

#include "widgets/QSFMLView.h"
#include <SFML/Graphics.hpp>

namespace OSSAM
{


class World : public QSFMLView
{
    public :
        World(QWidget* Parent, const QPoint& Position, const QSize& Size);
        World(QWidget*& Parent);

    private :
        void onInit() override;
        void onUpdate() override;

        sf::Texture mTexture;
        sf::Sprite mSprite;
};


}


#endif // WORLD_H
