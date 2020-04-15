#include "Particle.h"

Particle::Particle(Object* model, const QVector3D& velocity, float lifespan) : modelToRender_(model), velocity_(velocity), secondsLeftToLive_(lifespan) {

}

void Particle::updateAndDraw(unsigned int msSinceLastFrame, QMatrix4x4 world, QMatrix4x4 projection, QMatrix4x4 view) {

	secondsLeftToLive_ -= (float)msSinceLastFrame / 1000;
	particleTransform_.translate(velocity_);
	velocity_ *= 1.05;

	if (isDead()) {
		return;
	}

	modelToRender_->draw(world, view, projection, particleTransform_);


}