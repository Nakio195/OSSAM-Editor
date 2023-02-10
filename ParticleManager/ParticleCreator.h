#ifndef PARTICLECREATOR_H
#define PARTICLECREATOR_H

#include <QDialog>
#include "FileManager/FileModel.h"
#include "ParticleManager/Particle.h"
#include "Context.h"


namespace Ui {
class ParticleCreator;
}

class ParticleCreator : public QDialog
{
    Q_OBJECT

    public:
        explicit ParticleCreator(Context* context, QWidget *parent = nullptr);
        ~ParticleCreator();

        Particle getParticle();

        static Particle create(Context* context, QWidget *parent);

    public slots:
        void browseAsset();
        void pickColor();
        void setText(QString string);
        void setLifeTime(int life);

    private:
        Particle mParticle;

        Ui::ParticleCreator *ui;
        Context* mContext;
};

#endif // PARTICLECREATOR_H
