#include "Actor.h"

Actor::Actor() {
}

Actor::~Actor() {
}

bool Actor::Init() {
	UpdateWorldTransform();

	return true;
}

void Actor::SetPosition(Vector3 pos) {
	position = pos;
	UpdateWorldTransform();
}

void Actor::SetRotation(float rot) {
	rotation = rot;
	UpdateWorldTransform();
}

void Actor::SetScale(float s) {
	scale = s;
	UpdateWorldTransform();
}

void Actor::UpdateWorldTransform() {
	// TODO: Use own mat and vec
	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::rotate(model, rotation, glm::vec3(0.f, 0.f, 1.f)); // Around z axis
	model = glm::scale(model, glm::vec3(scale));
}
