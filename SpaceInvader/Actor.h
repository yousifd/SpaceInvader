#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Math.h"

class Game;

class Actor {
public:
	Actor();
	~Actor();

	bool Init(Game* _game);

	void SetPosition(Vector3 pos);
	const Vector3& GetPosition() { return position; };

	void SetRotation(float rot);
	const float& GetRotation() { return rotation; };

	void SetScale(Vector3 s);
	const Vector3& GetScale() { return scale; };

	glm::mat4 GetModel() { return model; };

	Game* GetGame() { return game; };

	Vector2 velocity = { 0.f, 0.f };

protected:
	int id;
	float xMin, xMax, yMin, yMax;
	Game* game;

private:
	void UpdateWorldTransform();

	static int count;
	Vector3 position = Vector3(0.f, 0.f, 0.f);
	float rotation = 0.f;
	Vector3 scale = { 1.f, 1.f, 1.f };
	glm::mat4 model = glm::mat4(1.f);
};

