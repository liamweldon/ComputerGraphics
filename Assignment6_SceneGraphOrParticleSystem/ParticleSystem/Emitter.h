#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <QtCore/QRandomGenerator>

#include "Particle.h"


class Emitter {
private:
    unsigned int msSinceLastEmit_;
protected:
    QVector<Particle*> particles_;
    QVector3D position_;
    QVector3D orientation_;
    unsigned int particlesPerSecond_;
    Object* particleModel_;
    QRandomGenerator randomGen_;
    bool canEmitParticle();

public:
    Emitter(const QVector3D& position, unsigned int pps, Object* particleModel);
    ~Emitter();
    void update(unsigned int msSinceLastFrame, QMatrix4x4 world, QMatrix4x4 projection, QMatrix4x4 view);
};