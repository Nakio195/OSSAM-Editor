#ifndef OSSAM_ParticleViewer_H
#define OSSAM_ParticleViewer_H

#include <SFML/Graphics.hpp>
#include <QQueue>
#include "widgets/QSFMLView.h"
#include "ParticleManager/Particle.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>


namespace OSSAM
{
    class Particle
    {
        public:
            float lifeTime;
            sf::Color color;
            sf::Vector2f position;
    };
}

class ParticleViewer : public QSFMLView
{
    Q_OBJECT

    public:
        ParticleViewer(QWidget* Parent, const QPoint& Position, const QSize& Size);
        ParticleViewer(QWidget*& Parent);
        ParticleViewer(QDialog*& Parent);

    public slots:
        void setColor(QColor color);
        void setLifeTime(float life);
        void setTexture(QString path);

        void setParticle(Particle part);
        void setEmitterSpeed(int speed);
        void setEmitterRate(int rate);

    private :
        void onInit() override;
        void onUpdate() override;
        void resizeEvent(QResizeEvent*) override;

    private:
        void addParticle(sf::Vector2f position);
        void addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const;
        void computeVertices() const;

    private:
        QQueue<OSSAM::Particle> mParticles;

        mutable sf::VertexArray mVertexArray;
        mutable bool mNeedsVertexUpdate;

        float elapsedTime;
        float mSpeed;
        float emitterPeriod;
        float emitterRate;
        sf::Vector2f emitterPosition;

    private:
        Particle mParticle;
        sf::Sprite mSprite;
        sf::Texture mTexture;
};


#endif // OSSAM_ParticleViewer_H
