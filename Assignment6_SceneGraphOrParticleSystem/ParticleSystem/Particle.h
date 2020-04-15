#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <iostream>

#include "Object.h"

class Particle {
protected:
    Object* modelToRender_;
    QMatrix4x4 particleTransform_;
    QVector3D velocity_;
    int msLeftToLive_;

public:
    Particle(Object* model, const QVector3D& velocity, unsigned int lifespanMs);

    void updateAndDraw(unsigned int msSinceLastFrame, QMatrix4x4 world, QMatrix4x4 projection, QMatrix4x4 view);
    bool isDead() const;
};