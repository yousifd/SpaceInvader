#include "Sprite.h"

#include "Game.h"

Sprite::Sprite() {
}

Sprite::~Sprite() {
}

bool Sprite::Init(const char* filename, Actor* _owner) {
	owner = _owner;

	if (!tex.Init(filename)) {
		printf("Failed to initialize texture when initializing sprite!\n;");
		return false;
	}

	owner->GetGame()->GetRenderer()->AddSprite(this);

	return true;
}

void Sprite::UploadUniforms(Shader* shader) {
	shader->UploadMatrix(&owner->GetModel(), "model");
	shader->UploadTexture(&tex, "tex", GL_TEXTURE0);
}
