#include "Vector2D.h" //!< Allows access to the vector2D header file.

//A float with the value of Pi.
float fPi = 3.14159265358;

//! This is the default constructor that sets the values of the vector to 0.
Vector2D::Vector2D(){
	m_faDataValues[0] = 0;
	m_faDataValues[1] = 0;
}

//! This constructor sets all the values of the vector to the float "allValues".
/*!
\param allValues - a float that sets both values in the array.
*/
Vector2D::Vector2D(float allValues){
	m_faDataValues[0] = allValues;
	m_faDataValues[1] = allValues;
}

//! This constructor sets the first value in the vector to x and sets the second value in the vector to y.
/*!
\param x - a float that sets the first value in the array.
\param y - a float that sets the second value in the array.
*/
Vector2D::Vector2D(float x, float y){
	m_faDataValues[0] = x;
	m_faDataValues[1] = y;
}

//! This function is used to set the values of the vector to x and y.
/*!
\param x - a float that sets the first value in the array.
\param y - a float that sets the second value in the array.
*/
void Vector2D::setValues(float x, float y){
	m_faDataValues[0] = x;
	m_faDataValues[1] = y;
}

void Vector2D::normalise()
{
	float mag = getMagnitude();
	m_faDataValues[0] = m_faDataValues[0] / mag;
	m_faDataValues[1] = m_faDataValues[1] / mag;
}

//! This function is used to get the X value.
float Vector2D::getX() const{
	return m_faDataValues[0];
}

//! This function is used to get the Y value.
float Vector2D::getY() const{
	return m_faDataValues[1];
}

//! This function is used to calculate the magnitude of a vector.
float Vector2D::getMagnitude() const{
	return float(sqrt((getX() * getX()) + (getY() * getY())));
}

//! This function is used to calcualte the angle between two vectors.
/*!
\param other - a Vector2D that is used to calculate the angle of a vector.
*/
float Vector2D::getAngle(const Vector2D& other) const{
	return float(180/fPi * acos((dotProduct(other)/(getMagnitude() * other.getMagnitude()))));
}

//! This function is used to calculate the dot product of two vectors.
/*!
\param other - a Vector2D used to calculate the dot product of two vectors. 
*/
float Vector2D::dotProduct(const Vector2D& other) const{
	return float((getX() * other.getX()) + ((getY() * other.getY())));
}

//! This function is used to calculate the cross product of two vectors.
/*!
\param other - a Vector2D used to calculate the cross product of two vectors.
*/
float Vector2D::crossProduct(const Vector2D& other) const{
	return float((getX() * other.getY()) - ((other.getX() * getY())));
}

//! This function is used to turn the vector into a unit vector.
Vector2D Vector2D::unitVector() const{
	return Vector2D((getX()/getMagnitude()), (getY()/getMagnitude()));
}

//! This function is used to subtract one vector from another.
/*!
\param other - a Vector2D that is subtracted from this Vector2D.
*/
Vector2D Vector2D::operator-(const Vector2D& other) const{
	return Vector2D((getX() - other.getX()), (getY() - other.getY()));
}

//! This function is used to add two vectors together.
/*!
\param other - a Vector2D that is added to this Vector2D.
*/
Vector2D Vector2D::operator+(const Vector2D& other) const{
	return Vector2D((getX() + other.getX()), (getY() + other.getY()));
}

//! This function is used to multiply two vectors together.
/*!
\param other - a Vector2D that is multiplied with this Vector2D.
*/
Vector2D Vector2D::operator*(const Vector2D& other) const{
	return Vector2D((getX() * other.getX()), (getY() * other.getY()));
}

//! This function is used to scale the vector.
/*!
\param scalar - a float that is multiplied with both members of this Vector2D.
*/
Vector2D Vector2D::operator*(const float scalar) const{
	return Vector2D((getX() * scalar), (getY() * scalar));
}

//! This function is used to set the x value of the vector.
/*!
\param x - a float that sets the first value in the array.
*/
void Vector2D::setX(float x){
	m_faDataValues[0] = x;
}

//! This function is used to set the y value of the vector.
/*!
\param y - a float that sets the second value in the array
*/
void Vector2D::setY(float y){
	m_faDataValues[1] = y;
}