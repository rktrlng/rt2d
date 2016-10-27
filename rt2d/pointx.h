/**
 * @file pointx.h
 *
 * @brief The Point_t header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>

/**
 * @brief The Point_t class is a helper class that makes it easier to define points in space.
 *
 */
// =================================================
// Class definition of Point_t<T>
// =================================================
template <class T>
class Point_t
{
public:
	/**
	 * @brief This is the Point constructor.
	 *
	 * It creates a Point at 0,0,0
	 *
	 */
	Point_t<T>();
	/**
	 * @brief This is the 2D Point constructor that creates coordinates instantly.
	 *
	 * @param xx
	 * The x value of the Point.
	 * @param yy
	 * The y value of the Point.
	 */
	Point_t<T>(T xx, T yy);
	/**
	 * @brief This is the 3D Point constructor that creates coordinates instantly.
	 *
	 * @param xx
	 * The x value of the Point.
	 * @param yy
	 * The y value of the Point.
	 * @param zz
	 * The z value of the Point.
	 */
	Point_t<T>(T xx, T yy, T zz);
	/**
	 * @brief This is the Point destructor.
	 *
	 * It cleans up the Point.
	 */
	virtual ~Point_t<T>();

	/**
	 * @brief The x value of the Point.
	 *
	 * This is a value on the horizontal axis.
	 *
	 * @var x
	 * The x value of the Point.
	 */
	T x;
	/**
	 * @brief The y value of the Point.
	 *
	 * This is a value on the vertical axis.
	 *
	 * @var y
	 * The y value of the Point.
	 */
	T y;
	/**
	 * @brief The z value of the Point.
	 *
	 * This is a value on the depth axis.
	 *
	 * @var z
	 * The z value of the Point.
	 */
	T z;

	// operator overloaders for another Point
	/**
	 * @brief returns the sum of two Points
	 *
	 * @param rhs
	 * The Point to be added
	 *
	 * @return
	 * the sum of two Points
	 */
	Point_t<T>& operator+=(const Point_t<T>& rhs);
	/**
	 * @brief returns the sum of two Points
	 *
	 * @param rhs
	 * The Point to be added
	 *
	 * @return
	 * the sum of two Points
	 */
	Point_t<T> operator+(const Point_t<T>& rhs) const;
	/**
	 * @brief returns the difference between two Points
	 *
	 * @param rhs
	 * The Point to be subtracted
	 *
	 * @return
	 * the difference between two Points
	 */
	Point_t<T>& operator-=(const Point_t<T>& rhs);
	/**
	 * @brief returns the difference between two Points
	 *
	 * @param rhs
	 * The Point to be subtracted
	 *
	 * @return
	 * the difference between two Points
	 */
	Point_t<T> operator-(const Point_t<T>& rhs) const;
	/**
	 * @brief returns the product of two Points
	 *
	 * @param rhs
	 * The Point to be multiplied
	 *
	 * @return
	 * the product of two Points
	 */
	Point_t<T>& operator*=(const Point_t<T>& rhs);
	/**
	 * @brief returns the product of two Points
	 *
	 * @param rhs
	 * The Point to be multiplied
	 *
	 * @return
	 * the product of two Points
	 */
	Point_t<T> operator*(const Point_t<T>& rhs) const;
	/**
	 * @brief returns the quotient of two Points
	 *
	 * @param rhs
	 * The Point to be divided
	 *
	 * @return
	 * the quotient of two Points
	 */
	Point_t<T>& operator/=(const Point_t<T>& rhs);
	/**
	 * @brief returns the quotient of two Points
	 *
	 * @param rhs
	 * The Point to be divided
	 *
	 * @return
	 * the quotient of two Points
	 */
	Point_t<T> operator/(const Point_t<T>& rhs) const;

	// operator overloaders for any number
	/**
	 * @brief returns the sum of the Point and any number
	 *
	 * @param rhs
	 * The number to be added
	 *
	 * @return
	 * the sum of the Point and any number
	 */
	Point_t<T>& operator+=(const T rhs);
	/**
	 * @brief returns the sum of the Point and any number
	 *
	 * @param rhs
	 * The number to be multiplied
	 *
	 * @return
	 * the sum of the Point and any number
	 */
	Point_t<T> operator+(const T rhs) const;
	/**
	 * @brief returns the difference of the Point and any number
	 *
	 * @param rhs
	 * The number to be subtracted
	 *
	 * @return
	 * the difference between the Point and any number
	 */
	Point_t<T>& operator-=(const T rhs);
	/**
	 * @brief returns the difference of the Point and any number
	 *
	 * @param rhs
	 * The number to be subtracted
	 *
	 * @return
	 * the difference of the Point and any number
	 */
	Point_t<T> operator-(const T rhs) const;
	/**
	 * @brief returns the product of the Point and any number
	 *
	 * @param rhs
	 * The number to be multiplied
	 *
	 * @return
	 * the product of the Point and any number
	 */
	Point_t<T>& operator*=(const T rhs);
	/**
	 * @brief returns the product of the Point and any number
	 *
	 * @param rhs
	 * The number to be multiplied
	 *
	 * @return
	 * the product of the Point and any number
	 */
	Point_t<T> operator*(const T rhs) const;
	/**
	 * @brief returns the quotient of the Point and any number
	 *
	 * @param rhs
	 * The number (divisor)
	 *
	 * @return
	 * the quotient of the Point and any number
	 */
	Point_t<T>& operator/=(const T rhs);
	/**
	 * @brief returns the quotient of the Point and any number
	 *
	 * @param rhs
	 * The number (divisor)
	 *
	 * @return
	 * the quotient of the Point and any number
	 */
	Point_t<T> operator/(const T rhs) const;

	// other operator overloaders
	/**
	 * @brief Overloads the == operator
	 *
	 * @param other
	 * The Point to compare with
	 *
	 * @return
	 * boolean. true if Points are the same
	 */
	bool operator==(const Point_t<T>& other) const;
	/**
	 * @brief Overloads the != operator
	 *
	 * @param other
	 * The Point to compare with
	 *
	 * @return
	 * boolean. true if Points are different
	 */
	bool operator!=(const Point_t<T>& other) const;
};

// =================================================
// Typedefs for Point_t<T>
// =================================================
// Point typedefs
/**
 * @brief A typedef for creating Point_t<int>
 *
 * Create a point of ints
 *
 * @var Pointi
 * A point of ints
 */
typedef Point_t<int> Pointi;
/**
 * @brief A typedef for creating Point_t<float>
 *
 * Create a point of floats
 *
 * @var Pointf
 * A point of floats
 */
typedef Point_t<float> Pointf;
/**
 * @brief A typedef for creating Point_t<double>
 *
 * Create a point of doubles
 *
 * @var Pointd
 * A point of doubles
 */
typedef Point_t<double> Pointd;
/**
 * @brief A typedef for creating a default Point
 *
 * Create a point of floats. The default.
 *
 * @var Point
 * A point of floats (default).
 */
typedef Pointf Point;
// 2D Point typedefs
/**
 * @brief A typedef for creating Point_t<int>
 *
 * Create a point of ints
 *
 * @var Point2i
 * A point of ints
 */
typedef Point_t<int> Point2i;
/**
 * @brief A typedef for creating Point_t<float>
 *
 * Create a point of floats
 *
 * @var Point2f
 * A point of floats
 */
typedef Point_t<float> Point2f;
/**
 * @brief A typedef for creating Point_t<double>
 *
 * Create a point of doubles
 *
 * @var Point2d
 * A point of doubles
 */
typedef Point_t<double> Point2d;
/**
 * @brief A typedef for creating a default Point2
 *
 * Create a point of floats. The default.
 *
 * @var Point2
 * A point of floats (default).
 */
typedef Point2f Point2;
// 3D Point typedefs
/**
 * @brief A typedef for creating Point_t<int>
 *
 * Create a point of ints
 *
 * @var Point3i
 * A point of ints
 */
typedef Point_t<int> Point3i;
/**
 * @brief A typedef for creating Point_t<float>
 *
 * Create a point of floats
 *
 * @var Point3f
 * A point of floats
 */
typedef Point_t<float> Point3f;
/**
 * @brief A typedef for creating Point_t<double>
 *
 * Create a point of doubles
 *
 * @var Point3d
 * A point of doubles
 */
typedef Point_t<double> Point3d;
/**
 * @brief A typedef for creating a default Point3
 *
 * Create a point of floats. The default.
 *
 * @var Point3
 * A point of floats (default).
 */
typedef Point3f Point3;

// =================================================
// Implementation of Point_t<T>
// =================================================

// constructors and destructor
template <class T>
Point_t<T>::Point_t()
{
	x = 0;
	y = 0;
	z = 0;
}

template <class T>
Point_t<T>::Point_t(T xx, T yy)
{
	x = xx;
	y = yy;
	z = 0;
}

template <class T>
Point_t<T>::Point_t(T xx, T yy, T zz)
{
	x = xx;
	y = yy;
	z = zz;
}

template <class T>
Point_t<T>::~Point_t()
{

}

// Add another Point (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator+=(const Point_t<T>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator+(const Point_t<T>& rhs) const
{
	return Point_t<T>(x+rhs.x, y+rhs.y, z+rhs.z);
}

// Subtract another Point (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator-=(const Point_t<T>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator-(const Point_t<T>& rhs) const
{
	return Point_t<T>(x+-rhs.x, y-rhs.y, z-rhs.z);
}

// Multiply with another Point (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator*=(const Point_t<T>& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator*(const Point_t<T>& rhs) const
{
	return Point_t<T>(x*rhs.x, y*rhs.y, z*rhs.z);
}

// Divide by another Point (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator/=(const Point_t<T>& rhs)
{
	// TODO: check for division by 0?
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator/(const Point_t<T>& rhs) const
{
	// TODO: check for division by 0?
	return Point_t<T>(x/rhs.x, y/rhs.y, z/rhs.z);
}

// Add any Number (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator+=(const T rhs)
{
	x += rhs;
	y += rhs;
	z += rhs;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator+(const T rhs) const
{
	return Point_t<T>(x+rhs, y+rhs, z+rhs);
}

// Subtract any Number (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator-=(const T rhs)
{
	x -= rhs;
	y -= rhs;
	z -= rhs;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator-(const T rhs) const
{
	return Point_t<T>(x-rhs, y-rhs, z-rhs);
}

// Multiply with any Number (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator*=(const T rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator*(const T rhs) const
{
	return Point_t<T>(x*rhs, y*rhs, z*rhs);
}

// Divide by any Number (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator/=(const T rhs)
{
	// TODO: check for division by 0?
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator/(const T rhs) const
{
	// TODO: check for division by 0?
	return Point_t<T>(x/rhs, y/rhs, z/rhs);
}

// operator == and != overloader
template <class T>
bool Point_t<T>::operator==(const Point_t<T>& other) const {
	return (x==other.x && y==other.y && z==other.z);
}

template <class T>
bool Point_t<T>::operator!=(const Point_t<T>& other) const {
	return !(*this == other);
}

// iostream << and >> overloader
/**
 * @param stream
 * @param ob
 */
template <class T>
std::ostream& operator<<(std::ostream& stream, Point_t<T> ob)
{
	stream << "(" << ob.x << ", " << ob.y << ", " << ob.z << ")";

	return stream;
}

/**
 * @param stream
 * @param ob
 */
template <class T>
std::istream& operator>>(std::istream& stream, Point_t<T>& ob)
{
	stream >> ob.x >> ob.y >> ob.z;

	return stream;
}

#endif /* POINT_H_ */
