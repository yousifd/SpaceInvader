#include <glm/glm.hpp>

#include "Player.h"

Player::Player() {
}

Player::~Player() {
	for (Missile* missile : missiles) {
		delete missile;
	}
}

bool Player::Init(Shader* shader) {
	if (!Actor::Init()) {
		printf("Failed to initialize Player's actor class!\n");
		return false;
	}

	SetPosition(Vector3(0.f, -.8f, 0.f));
	SetScale(0.4f);
	sprite.Init("ship.png", shader, this);

	return true;
}

void Player::Update(float delta) {
	Vector3 pos = GetPosition();
	glm::vec3 tmp = glm::vec3(pos.x, pos.y, pos.z) + (glm::vec3(velocity.x, velocity.y, 0.f) * delta);
	SetPosition(Vector3(tmp.x, tmp.y, tmp.z));

	for (Missile* missile : missiles) {
		missile->Update(delta);
	}
}

void Player::HandleKeyDown(SDL_KeyboardEvent event) {
	switch (event.keysym.sym) {
	case SDLK_d:
		if (!is_pressed[0]) {
			is_pressed[0] = true;
			velocity.x += speed;
		}
		break;
	case SDLK_a:
		if (!is_pressed[1]) {
			is_pressed[1] = true;
			velocity.x -= speed;
		}
		break;
	case SDLK_SPACE:
		Missile* missile = new Missile();
		missile->Init();
		missiles.push_back(Missile());
	}
}

void Player::HandleKeyUp(SDL_KeyboardEvent event) {
	switch (event.keysym.sym) {
	case SDLK_d:
		if (is_pressed[0]) {
			is_pressed[0] = false;
			velocity.x -= speed;
		}
		break;
	case SDLK_a:
		if (is_pressed[1]) {
			is_pressed[1] = false;
			velocity.x += speed;
		}
		break;
	}
}
