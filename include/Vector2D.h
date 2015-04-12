#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "math.h" //!< Allows access to the Math header file.

class Vector2D
{
protected:
	float m_faDataValues[2]; //!< The two numbers used in the Vector2D.
public:
	Vector2D(); //!< This is the default constructor that sets the values of the Vector2D to 0.
	Vector2D(float allValues); //!< This constructor sets all the values of the Vector2D to the float allValues.
	Vector2D(float x, float y); //!< This constructor sets the first value of the Vector2D to x and sets the second value of the Vector to y.
	void setValues(float x, float y); //!< This function is used to set the values of a Vector2D with two floats.
	void setX(float x); //!< This function is used to set the X value of a Vector2D.
	void setY(float y); //!< This function is used to set the Y value of a Vector2D.
	float getX() const; //!< This function is used to get the X value.
	float getY() const; //!< This function is used to get the Y value.
	float getMagnitude() const; //!< This function is used to calcualte the magnitude of a Vector2D.
	float getAngle(const Vector2D& other) const; //<! This function is used to calculate the angle between two Vector2Ds.
	float dotProduct(const Vector2D& other) const; //<! This function is used to calculate the dot product of two Vector2Ds.
	float crossProduct(const Vector2D& other) const; //<! This function is used to calculate the cross product of two Vector2Ds.
	Vector2D unitVector() const; //!< This function is used to turn the vector into a unit Vector2D.
	Vector2D operator-(const Vector2D& other) const; //!< This function is used to subtract one Vector2D from another.
	Vector2D operator+ (const Vector2D& other) const; //!< This function is used to add two Vector2Ds together.
	Vector2D operator*(const Vector2D& other) const; //!< This function is used to multiply two Vector2Ds together.
	Vector2D operator*(const float scalar) const; //!< This function is used to scale the Vector2D. 
	Vector2D operator/(const Vector2D& other); //!< This function is used to divide the Vector2D by another.
	void normalise();
};

#endif