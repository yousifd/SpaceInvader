#pragma once

constexpr float PI = 3.14159265359f;

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

	Vector4 operator* (const float other) {
		return Vector4(x * other, y * other, z * other, w * other);
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

	Vector3 operator* (const float other) {
		return Vector3(x * other, y * other, z * other);
	}

	bool operator== (const Vector3& other) {
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool operator!= (const Vector3& other) {
		return !(*this == other);
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

	Vector2 operator* (const float other) {
		return Vector2(x * other, y * other);
	}

	// TODO: Vector2
};
