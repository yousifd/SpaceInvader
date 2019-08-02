#include <algorithm>

#include "CollisionManager.h"

CollisionManager::CollisionManager() {
}

CollisionManager::~CollisionManager() {
	colliders.clear();
}

void CollisionManager::Update(float delta) {
	// TODO: Collision Detection
	for (Collider* a : colliders) {
		for (Collider* b : colliders) {
			if (a != b) {
				if (a->DidCollide(*b)) {
					a->callback(b->owner);
					b->callback(a->owner);
				}
			}
		}
	}
}

Collider* CollisionManager::CreateCollider(float x, float y, float w, float h, Actor* owner) {
	Collider* collider = new Collider();
	collider->Init(x, y, w, h, owner);
	colliders.push_back(collider);
	return collider;
}

void CollisionManager::RemoveCollider(Collider* collider) {
	auto it = std::find(colliders.begin(), colliders.end(), collider);
	if (it != colliders.end()) {
		colliders.erase(it);
	}
}