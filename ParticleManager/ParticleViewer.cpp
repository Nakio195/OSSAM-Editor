#include "ParticleViewer.h"
#include <QMessageBox>
#include <math.h>


ParticleViewer::ParticleViewer(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLView(Parent, Position, Size),
  mVertexArray(sf::Quads)
{
    mView.setCenter(0, 0);

    mSpeed = 0.2f;
    emitterPeriod = 0.2f;
    emitterRate = 0.2f;
    elapsedTime = 0.f;
    emitterPosition = sf::Vector2f(0,0);
}

ParticleViewer::ParticleViewer(QWidget*& Parent) : ParticleViewer(Parent, Parent->pos(), Parent->size())
{
}

ParticleViewer::ParticleViewer(QDialog*& Parent) : ParticleViewer(Parent, Parent->pos(), Parent->size())
{
}

void ParticleViewer::setColor(QColor color)
{
    mParticle.setColor(color);
}

void ParticleViewer::setTexture(QString path)
{
    mTexture.loadFromFile(path.toStdString());
    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mTexture.getSize().x/2, mTexture.getSize().y/2);
}

void ParticleViewer::setLifeTime(float life)
{
    mParticle.setLifeTime(life);
}

void ParticleViewer::setParticle(Particle part)
{
    mParticle = part;
}

void ParticleViewer::onInit()
{

}

void ParticleViewer::setEmitterSpeed(int speed)
{
    mSpeed = static_cast<float>(speed)/100.f;
}

void ParticleViewer::setEmitterRate(int rate)
{
    emitterRate = static_cast<float>(rate) / 1000.f;
}

void ParticleViewer::addParticle(sf::Vector2f position)
{
    OSSAM::Particle particle;
    particle.position = position;
    QColor qcolor = mParticle.getColor();
    sf::Color color(qcolor.red(), qcolor.green(), qcolor.blue());
    particle.color = color;
    particle.lifeTime = mParticle.getLifeTime();

    mParticles.push_back(particle);
}

void ParticleViewer::addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const
{
    sf::Vertex vertex;
    vertex.position = sf::Vector2f(worldX, worldY);
    vertex.texCoords = sf::Vector2f(texCoordX, texCoordY);
    vertex.color = color;

    mVertexArray.append(vertex);
}

void ParticleViewer::computeVertices() const
{
    sf::Vector2f size(mTexture.getSize());
    sf::Vector2f half = size / 2.f;

    // Refill vertex array
    mVertexArray.clear();
    for(const OSSAM::Particle& particle : mParticles)
    {
        sf::Vector2f pos = particle.position;
        QColor qcolor = mParticle.getColor();
        sf::Color color(qcolor.red(), qcolor.green(), qcolor.blue());

        float ratio = particle.lifeTime / mParticle.getLifeTime();
        color.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));

        addVertex(pos.x - half.x, pos.y - half.y, 0.f,    0.f,    color);
        addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f,    color);
        addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, color);
        addVertex(pos.x - half.x, pos.y + half.y, 0.f,    size.y, color);
    }
}


void ParticleViewer::onUpdate()
{
    elapsedTime += getFrameTime()/1000*mSpeed*2;
    emitterPosition.x = sin(elapsedTime)*50.f;
    emitterPosition.y = cos(elapsedTime)*50.f;
    emitterPeriod -= getFrameTime()/1000;

    if(emitterPeriod < 0.f)
    {
        addParticle(emitterPosition);
        emitterPeriod = emitterRate;
    }

    while (!mParticles.empty() && mParticles.front().lifeTime <= 0.f)
        mParticles.pop_front();

    for(OSSAM::Particle& particle : mParticles)
        particle.lifeTime -= static_cast<float>(getFrameTime()/1000.f);

    computeVertices();

    clear(sf::Color(mBackColor.red(), mBackColor.green(),mBackColor.blue()));

    sf::RenderStates states(&mTexture);
    draw(mVertexArray, states);

}

void ParticleViewer::resizeEvent(QResizeEvent*)
{
    sf::Vector2f size(static_cast<float>(QWidget::width()), static_cast<float>(QWidget::height()));
    sf::Vector2u sizeu(static_cast<unsigned int>(QWidget::width()), static_cast<unsigned int>(QWidget::height()));

    setSize(sizeu);
    mView.setSize(size);
    setView(mView);
}
