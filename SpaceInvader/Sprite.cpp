#include "Sprite.h"

Sprite::Sprite() {
}

Sprite::~Sprite() {
}

bool Sprite::Init(const char* filename, Shader* _shader, Actor* _owner) {
	shader = _shader;
	owner = _owner;

	Vertex vertices[] = { Vertex(-.5, .5, 0., 1., 0., 0., 1., 1., 0.), // top left
		Vertex(.5, .5, 0., 0., 1., 0., 1., 0., 0.), // top right
		Vertex(-.5, -.5, .0, 0., 0., 1., 1., 1., 1.), // bottom left
		Vertex(.5, -.5, .0, 0., 0., 0., 1., 0., 1.) }; // bottom right

	unsigned int indices[]{
		0, 1, 2,
		1, 2, 3,
	};

	if (!verts.Init(vertices, 4, indices, 6, shader)) {
		printf("Failed to initialize vertex array when initializing sprite!\n");
		return false;
	}

	if (!tex.Init(filename)) {
		printf("Failed to initialize texture when initializing sprite!\n;");
		return false;
	}

	return true;
}

void Sprite::Draw() {
	shader->UploadMatrix(&owner->GetModel(), "model");
	shader->UploadTexture(&tex, "tex", GL_TEXTURE0);
	shader->Activate();
	verts.Activate();
	glDrawElements(GL_TRIANGLES, verts.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}
