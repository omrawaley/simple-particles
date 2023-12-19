/*
Copyright 2023 Om Rawaley (@omrawaley)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "vector2.h"

namespace SimpleParticles
{
	Vector2::Vector2(float x, float y) : x{x}, y{y} {}

	Vector2& Vector2::operator+=(const Vector2& vector2)
	{
		this->x += vector2.x;
		this->y += vector2.y;

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& vector2)
	{
		this->x -= vector2.x;
		this->y -= vector2.y;

		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& vector2)
	{
		this->x *= vector2.x;
		this->y *= vector2.y;

		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& vector2)
	{
		this->x /= vector2.x;
		this->y /= vector2.y;

		return *this;
	}

	Vector2& Vector2::operator+(const Vector2& vector2)
	{
		static Vector2 newVector;

		newVector.x = this->x + vector2.x;
		newVector.y = this->y + vector2.y;

		return newVector;
	}

	Vector2& Vector2::operator-(const Vector2& vector2)
	{
		static Vector2 newVector;

		newVector.x = this->x - vector2.x;
		newVector.y = this->y - vector2.y;

		return newVector;
	}

	Vector2& Vector2::operator*(const Vector2& vector2)
	{
		static Vector2 newVector;

		newVector.x = this->x * vector2.x;
		newVector.y = this->y * vector2.y;

		return newVector;
	}

	Vector2& Vector2::operator/(const Vector2& vector2)
	{
		static Vector2 newVector;

		newVector.x = this->x / vector2.x;
		newVector.y = this->y / vector2.y;

		return newVector;
	}
}