#ifndef PARTICLECREATOR_H
#define PARTICLECREATOR_H

#include <QDialog>

namespace Ui {
class ParticleCreator;
}

class ParticleCreator : public QDialog
{
    Q_OBJECT

public:
    explicit ParticleCreator(QWidget *parent = nullptr);
    ~ParticleCreator();

private:
    Ui::ParticleCreator *ui;
};

#endif // PARTICLECREATOR_H
