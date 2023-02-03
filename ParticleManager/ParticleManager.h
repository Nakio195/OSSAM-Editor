#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <QWidget>

namespace Ui {
class ParticleManager;
}

class ParticleManager : public QWidget
{
    Q_OBJECT

public:
    explicit ParticleManager(QWidget *parent = nullptr);
    ~ParticleManager();

private:
    Ui::ParticleManager *ui;
};

#endif // PARTICLEMANAGER_H
