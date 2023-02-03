#include "OSSAM_World.h"

using namespace OSSAM;

World::World(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLView(Parent, Position, Size)
{

}

World::World(QWidget*& Parent) : QSFMLView(Parent, Parent->pos(), Parent->size())
{

}

void World::onInit()
{
    // On charge une image
    mTexture.loadFromFile("Ressources/Sprite/Player/Player.png");

    // On paramètre le sprite
    mSprite.setTexture(mTexture);
    mSprite.setPosition(200, 200);
    mSprite.setOrigin(sf::Vector2f(mTexture.getSize()/2u));
}

void World::onUpdate()
{
    // On efface l'écran
    clear(sf::Color(128, 128, 128));

    // Une petite rotation du sprite

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        mSprite.rotate(-1);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        mSprite.rotate(1);

    // Et on l'affiche
    draw(mSprite);
}
