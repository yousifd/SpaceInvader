#include <functional>

#include <glm/glm.hpp>

#include "Player.h"
#include "Math.h"
#include "Game.h"

Player::Player() {
}

Player::~Player() {
}

bool Player::Init(Game* _game) {
	if (!Actor::Init(_game)) {
		printf("Failed to initialize Player's actor class!\n");
		return false;
	}

	speed = std::stof(game->GetVariable("Player", "speed"));
	scalarScale = std::stof(game->GetVariable("Player", "scale"));
	fire_wait_time = std::stof(game->GetVariable("Player", "fire_wait_time"));
	filename = game->GetVariable("Player", "filename");

	game->vars.BindCallback("Player", std::bind(&Player::VariableUpdateCallback, this, std::placeholders::_1));

	if (!sprite.Init(filename.c_str(), this)) {
		printf("Failed to initialize Player's sprite!\n");
		return false;
	}

	// TODO: Bound to edge of sprite instead of middle
	// TODO: Move this to collision detection?
	//printf("Before:\nxMin: %f\nxMax: %f\nyMin: %f\nyMax: %f\n", xMin, xMax, yMin, yMax);

	//xMin += (sprite.tex.width / 2.f);
	//xMax -= (sprite.tex.width / 2.f);
	//yMin += (sprite.tex.height / 2.f);
	//yMax -= (sprite.tex.height / 2.f);

	//printf("After:\nxMin: %f\nxMax: %f\nyMin: %f\nyMax: %f\n", xMin, xMax, yMin, yMax);

	SetPosition(Vector3(0.f, yMin + 50.f, 0.f));
	SetScale(Vector3(scalarScale, scalarScale, 0.f));

	fire_timer = fire_wait_time;

	return true;
}

void Player::Update(float delta) {
	if (updateSprite) {
		updateSprite = false;
		sprite.~Sprite();
		if (!sprite.Init(filename.c_str(), this)) {
			printf("Failed to initialize Player's sprite!\n");
		}
	}

	Vector3 pos = GetPosition();
	glm::vec3 tmp = glm::vec3(pos.x, pos.y, pos.z) + (glm::vec3(velocity.x, velocity.y, 0.f) * delta);
	SetPosition(Vector3(tmp.x, tmp.y, tmp.z));

	fire_timer += delta;
}

void Player::VariableUpdateCallback(const std::map<std::string, std::string>& kvs) {
	for (auto& kv : kvs) {
		std::string key = kv.first;
		if (key == "filename") {
			// Can only update openGL stuff in the main thread :(
			filename = kv.second;
			updateSprite = true;
		}
		else if (key == "speed") {
			float speed = std::stof(kv.second);
		} else if (key == "scale") {
			float _scale = std::stof(kv.second);
			SetScale(Vector3(_scale, _scale, 0.f));
			scalarScale = _scale;
		} else if (key == "fire_wait_time") {
			fire_wait_time = std::stof(kv.second);
		}
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
		if (!is_pressed[2] && fire_timer >= fire_wait_time) {
			is_pressed[2] = true;
			fire_timer = 0.f;
			Missile* missile = new Missile();
			missile->Init(game, this);
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
