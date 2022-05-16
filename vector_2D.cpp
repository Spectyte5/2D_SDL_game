#include "vector_2D.h"


Vector2D::Vector2D() {

	x = 0;
	y = 0;
}

Vector2D::Vector2D(float x, float y) {

	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vect) {

	this->x += vect.x;
	this->y += vect.y;

	//return vect
	return *this;
}
Vector2D& Vector2D::Subtract(const Vector2D& vect) {

	this->x -= vect.x;
	this->y -= vect.y;

	return *this;
}
Vector2D& Vector2D::Multiply(const Vector2D& vect) {

	this->x *= vect.x;
	this->y *= vect.y;

	return *this;
}
Vector2D& Vector2D::Divide(const Vector2D& vect) {

	this->x /= vect.x;
	this->y /= vect.y;

	return *this;
}

Vector2D& operator+ (Vector2D& v1, const Vector2D& v2) {

	//return v1 + v2
	return v1.Add(v2);
}

Vector2D& operator- (Vector2D& v1, const Vector2D& v2) {

	return v1.Subtract(v2);
}

Vector2D& operator* (Vector2D& v1, const Vector2D& v2) {

	return v1.Multiply(v2);
}

Vector2D& operator/ (Vector2D& v1, const Vector2D& v2) {

	return v1.Divide(v2);
}

Vector2D& Vector2D::operator +=(const Vector2D& vect) {

	//return vect + vect
	return this->Add(vect);
}

Vector2D& Vector2D::operator -=(const Vector2D& vect) {

	return this->Subtract(vect);
}

Vector2D& Vector2D::operator *=(const Vector2D& vect) {

	return this->Multiply(vect);
}

Vector2D& Vector2D::operator /=(const Vector2D& vect) {

	return this->Divide(vect);
}

std::ostream& operator << (std::ostream& output, const Vector2D& vect) {
	
	output << "(" << vect.x << "," << vect.y << ")"; 
		return output;
}

Vector2D& Vector2D::operator*(const int& i) {

	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::Zero() {

	this->x = 0;
	this->y = 0;

	return *this; 
}