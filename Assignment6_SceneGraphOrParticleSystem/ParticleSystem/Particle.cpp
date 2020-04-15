#include "Particle.h"

Particle::Particle(Object* model, const QVector3D& velocity, unsigned int lifespanMs) : modelToRender_(model), velocity_(velocity) {
	this->msLeftToLive_ = lifespanMs;
	particleTransform_.setToIdentity();
}

void Particle::updateAndDraw(unsigned int msSinceLastFrame, QMatrix4x4 world, QMatrix4x4 projection, QMatrix4x4 view) {

	this->msLeftToLive_ -= msSinceLastFrame;
	particleTransform_.translate(velocity_);
	velocity_ *= 1.05f;

	if (isDead()) {
		return;
	}
	modelToRender_->draw(world, view, projection, particleTransform_);


}



bool Particle::isDead() const {
	return msLeftToLive_ <= 0; 
}