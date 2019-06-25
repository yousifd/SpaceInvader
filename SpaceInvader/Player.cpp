#include <glm/glm.hpp>

#include "Player.h"
#include "Math.h"
#include "Game.h"

Player::Player() {
}

Player::~Player() {
}

bool Player::Init(Game* _game, Shader* _shader) {
	if (!Actor::Init(_game)) {
		printf("Failed to initialize Player's actor class!\n");
		return false;
	}

	shader = _shader;
	if (!sprite.Init("ship.png", shader, this)) {
		printf("Failed to initialize Player's sprite!\n");
		return false;
	}

	// TODO: Bound to edge of sprite instead of middle
	//printf("Before:\nxMin: %f\nxMax: %f\nyMin: %f\nyMax: %f\n", xMin, xMax, yMin, yMax);

	//xMin += (sprite.tex.width / 2.f);
	//xMax -= (sprite.tex.width / 2.f);
	//yMin += (sprite.tex.height / 2.f);
	//yMax -= (sprite.tex.height / 2.f);

	//printf("After:\nxMin: %f\nxMax: %f\nyMin: %f\nyMax: %f\n", xMin, xMax, yMin, yMax);

	SetPosition(Vector3(0.f, yMin + 50.f, 0.f));
	SetScale(Vector3(scale, scale, 0.f));

	return true;
}

void Player::Update(float delta) {
	Vector3 pos = GetPosition();
	glm::vec3 tmp = glm::vec3(pos.x, pos.y, pos.z) + (glm::vec3(velocity.x, velocity.y, 0.f) * delta);
	SetPosition(Vector3(tmp.x, tmp.y, tmp.z));

	fire_timer += delta;
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
		if (!is_pressed[2] && fire_timer >= fire_wait_time) {
			fire_timer = 0.f;
			is_pressed[2] = true;
			Missile* missile = new Missile();
			missile->Init(game, this, shader);
			game->AddMissile(missile);
		}
		break;
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
	case SDLK_SPACE:
		if (is_pressed[2]) {
			is_pressed[2] = false;
		}
		break;
	}
}
