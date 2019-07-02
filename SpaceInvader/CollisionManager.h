#pragma once

#include <cmath>
#include <vector>
#include <map>

#include "Actor.h"

// TODO: Collision Detection
struct Collider {
	void Init(float _x, float _y, float _w, float _h, Actor* _owner) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		owner = _owner;
	}

	bool DidCollide(const Collider& b) {
		return (abs(x - b.x) * 2 < (w + b.w)) &&
			(abs(y - b.y) * 2 < (h + b.h));
	}

	float x, y, w, h;
	Actor* owner;
};

class CollisionManager {
public:
	CollisionManager();
	~CollisionManager();

	void Update(float delta);

	Collider* CreateCollider(float x, float y, float w, float h, Actor* owner);
	void RemoveCollider(Collider* collider);

private:
	std::vector<Collider*> colliders;
};

