#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

#include "Object.h"

class Particle {
protected:
    Object* modelToRender_;
    QMatrix4x4 particleTransform_;
    QVector3D velocity_;
    float secondsLeftToLive_;

public:
    Particle(Object* model, const QVector3D& velocity, float lifespan);

    void updateAndDraw(unsigned int msSinceLastFrame, QMatrix4x4 world, QMatrix4x4 projection, QMatrix4x4 view);
    bool isDead() const { return secondsLeftToLive_ <= 0.0; }
};