#include "Emitter.h"


Emitter::Emitter(const QVector3D& position, unsigned int pps, Object* particleModel) : position_(position), particlesPerSecond_(pps), particleModel_(particleModel) {

}

Emitter::~Emitter() {
    for (int i = 0; i < particles_.size(); i++) {
        delete particles_.at(i);
    }
}
    void Emitter::update(unsigned int msSinceLastFrame, QMatrix4x4 world, QMatrix4x4 projection, QMatrix4x4 view) {
        
        world.translate(position_);
        

        for (int i = 0; i < particles_.size(); i++) {
            Particle* p = particles_.at(i);
            p->updateAndDraw(msSinceLastFrame, world, projection, view);
        }
      
        msSinceLastEmit_ += msSinceLastFrame;
        if (canEmitParticle()) {
            msSinceLastEmit_ = 0;
            QVector3D velocity = QVector3D(2.0f * (randomGen_.generateDouble() - 0.5f), -1 * abs(randomGen_.generateDouble()), 2.0f * (randomGen_.generateDouble() - 0.5f));
            Particle* newP = new Particle(particleModel_, velocity, 1000);
            particles_.append(newP);
        }


        while (!particles_.isEmpty() && particles_.at(0)->isDead()) {
            particles_.removeFirst();
        }

    }

    bool Emitter::canEmitParticle() {
        return msSinceLastEmit_ > 1000 / particlesPerSecond_;
    }



