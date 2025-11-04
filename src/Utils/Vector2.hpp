#pragma once

#include <Utils/Math.hpp>
#include <iostream>

namespace sw::utils
{
	template <typename T>
	struct Vector2
	{
		T x;
		T y;

		Vector2();
		Vector2(T x, T y);
		explicit Vector2(T xy);

		// implicit
		template <typename U>
		Vector2(const Vector2<U>& vect);

		// apply sign() to each coordinate
		Vector2<int32_t> Sign() const;

		Vector2<T> operator+=(const Vector2<T>& other);
		Vector2<T> operator-=(const Vector2<T>& other);
		Vector2<T> operator*=(T a);
		Vector2<T> operator/=(T a);
		Vector2<T> operator%=(T a);

		// True if true for both coordinates
		bool operator<=(const Vector2<T>& other) const;
		// True if true for both coordinates
		bool operator<(const Vector2<T>& other) const;
		// True if true for both coordinates
		bool operator>=(const Vector2<T>& other) const;
		// True if true for both coordinates
		bool operator>(const Vector2<T>& other) const;

		// True if one of the coordinates is different from zero
		operator bool() const;

		std::string toString()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}
	};

	template <typename LeftT, typename RightT>
	auto operator+(const Vector2<LeftT>& left, const Vector2<RightT>& right);
	template <typename LeftT, typename RightT>
	auto operator-(const Vector2<LeftT>& left, const Vector2<RightT>& right);
	template <typename VectorT, typename ScalarT>
	auto operator*(const Vector2<VectorT>&, const ScalarT&);
	template <typename VectorT, typename ScalarT>
	auto operator/(const Vector2<VectorT>&, const ScalarT&);
	template <typename VectorT, typename ScalarT>
	auto operator%(const Vector2<VectorT>&, const ScalarT&);

	template <typename T>
	Vector2<T>::Vector2() :
			x(0),
			y(0)
	{}

	template <typename T>
	Vector2<T>::Vector2(T x, T y) :
			x(x),
			y(y)
	{}

	template <typename T>
	Vector2<T>::Vector2(T xy) :
			x(xy),
			y(xy)
	{}

	template <typename T>
	template <typename U>
	Vector2<T>::Vector2(const Vector2<U>& vect) :
			x(T(vect.x)),
			y(T(vect.y))
	{}

	template <typename T>
	Vector2<int32_t> Vector2<T>::Sign() const
	{
		return Vector2<int32_t>(utils::Sign(x), utils::Sign(y));
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator+=(const Vector2<T>& other)
	{
		x += other.x;
		y += other.y;
		return std::move(*this);
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator-=(const Vector2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return std::move(*this);
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator*=(T a)
	{
		x *= a;
		y *= a;
		return std::move(*this);
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator/=(T a)
	{
		x /= a;
		y /= a;
		return std::move(*this);
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator%=(T a)
	{
		x %= a;
		y %= a;
		return std::move(*this);
	}

	template <typename T>
	bool Vector2<T>::operator<=(const Vector2<T>& other) const
	{
		return x <= other.x && y <= other.y;
	}

	template <typename T>
	bool Vector2<T>::operator<(const Vector2<T>& other) const
	{
		return x < other.x && y < other.y;
	}

	template <typename T>
	bool Vector2<T>::operator>=(const Vector2<T>& other) const
	{
		return x >= other.x && y >= other.y;
	}

	template <typename T>
	bool Vector2<T>::operator>(const Vector2<T>& other) const
	{
		return x > other.x && y > other.y;
	}

	template <typename T>
	Vector2<T>::operator bool() const
	{
		return x != 0 || y != 0;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ')';
		return os;
	}

	template <typename LeftT, typename RightT>
	auto operator+(const Vector2<LeftT>& left, const Vector2<RightT>& right)
	{
		auto x = left.x + right.x;
		return Vector2<decltype(x)>(x, left.y + right.y);
	}

	template <typename LeftT, typename RightT>
	auto operator-(const Vector2<LeftT>& left, const Vector2<RightT>& right)
	{
		auto x = left.x - right.x;
		return Vector2<decltype(x)>(x, left.y - right.y);
	}

	template <typename VectorT, typename ScalarT>
	auto operator*(const Vector2<VectorT>& vector, const ScalarT& scalar)
	{
		auto x = vector.x * scalar;
		return Vector2<decltype(x)>(x, vector.y * scalar);
	}

	template <typename VectorT, typename ScalarT>
	auto operator/(const Vector2<VectorT>& vector, const ScalarT& scalar)
	{
		auto x = vector.x / scalar;
		return Vector2<decltype(x)>(x, vector.y / scalar);
	}

	template <typename VectorT, typename ScalarT>
	auto operator%(const Vector2<VectorT>& vector, const ScalarT& scalar)
	{
		auto x = vector.x % scalar;
		return Vector2<decltype(x)>(x, vector.y % scalar);
	}

	typedef Vector2<int32_t> Vector2i;
}  // namespace sw::utils
