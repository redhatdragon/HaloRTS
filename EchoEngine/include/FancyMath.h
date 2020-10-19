#pragma once

template<typename T>
struct Vec2D {
	T x, y;
	Vec2D() {};
	Vec2D(T _x, T _y) { x = _x; y = _y; };
	__forceinline void operator+=(Vec2D& other) {
		x += other.x;
		y += other.y;
	}
	__forceinline void operator-=(Vec2D& other) {
		x -= other.x;
		y -= other.y;
	}
	__forceinline void operator/=(T num) {
		x /= num;
		y /= num;
	}
	__forceinline void operator*=(T num) {
		x = x * num;
		y = y * num;
	}
	__forceinline Vec2D<T> operator+(Vec2D& other) {
		return { x + other.x, y + other.y };
	}
	__forceinline Vec2D<T> operator-(Vec2D& other) {
		return { x - other.x, y - other.y };
	}
	__forceinline Vec2D<T> operator/(T num) {
		return { x / num, y / num };
	}
	__forceinline Vec2D<T> operator*(T num) {
		return { x * num, y * num };
	}
	__forceinline bool isZero() {
		if (x == 0 && y == 0)
			return true;
		return false;
	}
	__forceinline void normalize(uint32_t unit = 1) {
		auto dist = getDistance();
		if (dist != 0) {
			x /= dist / unit; y /= dist / unit;
		}
	}
	__forceinline double getDistance() {
		return sqrt(x * x + y * y);
	}
};