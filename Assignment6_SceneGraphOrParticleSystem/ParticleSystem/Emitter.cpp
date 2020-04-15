#include "Emitter.h"


Emitter::Emitter(const QVector3D& position, const QVector3D& orientation, unsigned int pps, Object* particleModel) : position_(position), orientation_(orientation), particlesPerSecond_(pps), particleModel_(particleModel) {

}

Emitter::~Emitter() {

}
    void Emitter::update(unsigned int msSinceLastFrame, QMatrix4x4 world, QMatrix4x4 projection, QMatrix4x4 view) {
        for (int i = 0; i < particles_.size(); i++) {
            Particle p = particles_.at(i);
            p.updateAndDraw(msSinceLastFrame, world, projection, view);
        }
        float sSinceLastFrame = (float)msSinceLastFrame / 1000;
        int particlesToEmit = sSinceLastFrame * particlesPerSecond_;

        for (int i = 0; i <= particlesToEmit; i++) {
            QVector3D velocity = QVector3D(randomGen_.generateDouble(), -1 * abs(randomGen_.generateDouble()), randomGen_.generateDouble());
            Particle newP = Particle(particleModel_, velocity, 5.0f);
            particles_.append(newP);
        }

        while (!particles_.isEmpty() && particles_.at(0).isDead()) {
            particles_.removeFirst();
        }

    }



