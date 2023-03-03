#ifndef WEAPON_H
#define WEAPON_H


class Weapon
{
    public:
        enum Type
            {
                Laser1,
                Laser2,
                Laser3,
                Missile,
                WeaponsCount
            };

            struct Canon
            {
                Canon(sf::Vector2f position, float angle, Projectile::Type projectile, Animation::Type blast) :
                    position(position),
                    angle(angle),
                    projectile(projectile),
                    blast_Anim(blast)
                {
                }

                sf::Vector2f position;
                float angle;
                Projectile::Type projectile;
                Animation::Type blast_Anim;
            };

    public:
        Weapon();

    private:

        Weapon::Type mType;

        float  mFireRate;        //Cadence de tir en tir/s
        std::vector<Cannon> mCannons; // x, y , theta

        bool mNeedAmmo;
        int mAmmo;

        Command mFireCommand;

        bool mFire;
        Timer mReloadTimer;
        sf::Sprite mSprite;
        Sounds::ID mBlastSound;

        //Textures et anim
        std::vector<Animation> mBlastAnims;

};

#endif // WEAPON_H
