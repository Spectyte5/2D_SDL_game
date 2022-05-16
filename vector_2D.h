#pragma once
#include <iostream>
class Vector2D {

public:

	float x;
	float y;

	//default constructor
	Vector2D();
	//constructor with x and y values
	Vector2D(float x, float y);

	//vector operations: add two vectors: v1.add(v2) equals to v1+v2 etc.
	Vector2D& Add(const Vector2D& vect);
	Vector2D& Subtract(const Vector2D& vect);
	Vector2D& Multiply(const Vector2D& vect);
	Vector2D& Divide(const Vector2D& vect);

	//vector +,-,*,/ operators overloading:
	friend Vector2D& operator+ (Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator- (Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator* (Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/ (Vector2D& v1, const Vector2D& v2);

	//vector +=, -+, *=, /= operators overloading:
	Vector2D& operator+=(const Vector2D& vect);
	Vector2D& operator-=(const Vector2D& vect);
	Vector2D& operator*=(const Vector2D& vect);
	Vector2D& operator/=(const Vector2D& vect);

	//multiply our vector by scale
	Vector2D& operator*(const int &i);

	//zero our vector
	Vector2D& Zero();

	//overload << opearator:
	friend std::ostream& operator << (std::ostream& output, const Vector2D& vect);

};