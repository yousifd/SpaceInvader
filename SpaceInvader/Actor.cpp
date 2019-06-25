#include "Actor.h"
#include "Game.h"

int Actor::count;

Actor::Actor() {
}

Actor::~Actor() {
	printf("Actor with ID %d destroyed!\n", id);
}

bool Actor::Init(Game* _game) {
	id = count++;
	printf("ID: %d\n", id);
	game = _game;
	xMin = -game->GetRenderer()->width / 2.f;
	xMax = game->GetRenderer()->width / 2.f;
	yMin = -game->GetRenderer()->height / 2.f;
	yMax = game->GetRenderer()->height / 2.f;
	UpdateWorldTransform();

	return true;
}

void Actor::SetPosition(Vector3 pos) {
	position = pos;
	position.x = position.x < xMin ? xMin : position.x;
	position.x = position.x > xMax ? xMax : position.x;
	position.y = position.y < yMin ? yMin : position.y;
	position.y = position.y > yMax ? yMax : position.y;

	UpdateWorldTransform();
}

void Actor::SetRotation(float rot) {
	rotation = rot;
	UpdateWorldTransform();
}

void Actor::SetScale(Vector3 s) {
	scale = s;
	UpdateWorldTransform();
}

void Actor::UpdateWorldTransform() {
	// TODO: Use own mat and vec
	model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::rotate(model, rotation, glm::vec3(0.f, 0.f, 1.f)); // Around z axis
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
}
