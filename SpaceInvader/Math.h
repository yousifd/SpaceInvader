#pragma once

struct Vector4 {
	float x, y, z, w;

	Vector4() {
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	Vector4(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	// TODO: Vector4
};

struct Vector3 {
	float x, y, z;

	Vector3() {
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	Vector3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	// TODO: Vector3
};

struct Vector2 {
	float x, y;

	Vector2() {
		x = 0.f;
		y = 0.f;
	}

	Vector2(float _x, float _y) {
		x = _x;
		y = _y;
	}

	// TODO: Vector2
};
