#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Math.h"

class Actor {
public:
	Actor();
	~Actor();

	bool Init();

	void SetPosition(Vector3 pos);
	const Vector3& GetPosition() { return position; };

	void SetRotation(float rot);
	const float& GetRotation() { return rotation; };

	void SetScale(float s);
	const float& GetScale() { return scale; };

	glm::mat4 GetModel() { return model; };

	void UpdateWorldTransform();

	Vector2 velocity = { 0.f, 0.f };

private:
	Vector3 position = Vector3(0.f, 0.f, 0.f);
	float rotation = 0.f;
	float scale = 1.f;
	glm::mat4 model = glm::mat4(1.f);
};

