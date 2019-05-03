/**
 * @file vectorx.h
 *
 * @brief The VectorX_t header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef VECTORX_H_
#define VECTORX_H_

#include <cmath>
#include <rt2d/pointx.h>

/**
 * @brief pi (180 deg)
 * @var PI
 */
#define PI			3.1415926535897932384626433832795
/**
 * @brief pi/2 (90 deg)
 * @var HALF_PI
 */
#define HALF_PI		1.5707963267948966192313216916398
/**
 * @brief pi*2 (360 deg)
 * @var TWO_PI
 */
#define TWO_PI		6.283185307179586476925286766559
/**
 * @brief convert degrees to radians
 * @var DEG_TO_RAD
 */
#define DEG_TO_RAD	0.017453292519943295769236907684886
/**
 * @brief convert radians to degrees
 * @var RAD_TO_DEG
 */
#define RAD_TO_DEG	57.295779513082320876798154814105

/**
 * @brief A helper class to calculate distances and angles
 *
 * Extends Point. A Vector_t<T> contains the end position, but also direction.
 * The origin is always 0,0,0
 *
 * You will probably use this mostly as a Vector2. It is in fact a Vector3,
 * but it should be transparent enough not to notice.
 */
// =================================================
// Class definition of VectorX_t<T>
// =================================================
template <class T>
class VectorX_t : public Point_t<T>
{
public:
	/**
	 * @brief Default Vector_t<T> constructor.
	 *
	 * Creates a Vector_t<T> with endpoint 0,0,0
	 * Length = 0
	 */
	VectorX_t<T>();
	/**
	 * @brief Creates a Vector2 with endpoint xx,yy
	 *
	 * This is an overloaded Vector2 constructor.
	 *
	 * @param xx
	 * The x position of the Vector2.
	 * @param yy
	 * The y position of the Vector2.
	 */
	VectorX_t<T>(T xx, T yy);
	/**
	 * @brief Creates a Vector3 with endpoint xx,yy,zz
	 *
	 * This is an overloaded Vector3 constructor.
	 *
	 * @param xx
	 * The x position of the Vector3.
	 * @param yy
	 * The y position of the Vector3.
	 * @param zz
	 * The z position of the Vector3.
	 */
	VectorX_t<T>(T xx, T yy, T zz);
	/**
	 * @brief Creates a Vector_t<T> with endpoint Point_t<T> p
	 *
	 * This is an overloaded Vector_t<T> constructor.
	 *
	 * @param p
	 * The position of the Vector_t<T> as a Point.
	 */
	VectorX_t<T>(Point_t<T> p);
	/**
	 * @brief Creates a Vector_t<T> with startingpoint begin and endpoint end
	 *
	 * This is an overloaded Vector_t<T> constructor.
	 *
	 * @param begin
	 * The origin of the Vector_t<T>
	 * @param end
	 * The endpoint of the Vector_t<T>.
	 */
	VectorX_t<T>(Point_t<T> begin, Point_t<T> end);
	/**
	 * @brief This is the Vector_t<T> destructor.
	 *
	 * Clean up the Vector_t<T>.
	 */
	virtual ~VectorX_t();

	// length, angle, normalize, dot
	/**
	 * @brief Get the length of the Vector_t<T>
	 *
	 * Returns the length of the Vector_t<T> (pythagoras)
	 *
	 * @return T
	 * The length of the Vector_t<T>
	 */
	const T getLength() const;
	/**
	 * @brief Get the squared length of the Vector_t<T>
	 *
	 * Returns the squared length of the Vector_t<T>
	 *
	 * @return T
	 * The squared length of the Vector_t<T>
	 */
	const T getLengthSquared() const;
	/**
	 * @brief Set the length of the Vector_t<T>
	 *
	 * Sets the length of the Vector_t<T>
	 *
	 * @return void
	 */
	void setLength(T length);
	/**
	 * @brief Get the angle of the Vector2 in radians on the X-axis
	 *
	 * @return angle
	 * The angle of the Vector2 in radians
	 */
	const T getAngle() const;
	/**
	 * @brief Get the angle of the Vector2 in degrees on the X-axis
	 *
	 * @return angle
	 * The angle of the Vector2 in degrees
	 */
	const T getAngleDeg() const;
	/**
	 * @brief Get the angle between this Vector_t<T>, and another Vector_t<T> in radians
	 *
	 * @return angle
	 * The angle between this Vector_t<T>, and another Vector_t<T> in radians
	 */
	const T getAngle(const VectorX_t<T>& other) const;
	/**
	 * @brief Get the angle between this Vector_t<T>, and another Vector_t<T> in degrees
	 *
	 * @return angle
	 * The angle between this Vector_t<T>, and another Vector_t<T> in degrees
	 */
	const T getAngleDeg(const VectorX_t<T>& other) const;
	/**
	 * @brief Get the normalized Vector_t<T>.
	 *
	 * @return Vector_t<T>
	 * Returns a Vector_t<T> with length 1.
	 */
	const VectorX_t<T> getNormalized() const;
	/**
	 * @brief normalize this Vector_t<T>
	 */
	void normalize();
	/**
	 * @brief Get a lerped Vector_t<T> according to some fraction (between 0 and 1)
	 */
	void lerp(T frac);
	/**
	 * @brief Get a copy of a lerped Vector_t<T> according to some fraction (between 0 and 1)
	 *
	 * @return Vector_t<T>
	 * Returns a lerped Vector_t<T>.
	 */
	const VectorX_t<T> getLerped(T frac) const;
	/**
	 * @brief Get the dot product of this and another Vector_t<T>.
	 *
	 * @return Scalar
	 * Returns the dot product
	 */
	const T dot(const VectorX_t<T>& other) const;
	/**
	 * @brief Get the cross product of this and another Vector3.
	 * This only makes sense with a Vector3
	 *
	 * @return Vector_t<T>
	 * the cross product
	 */
	const VectorX_t<T> cross(const VectorX_t<T>& other) const;
	/**
	 * @brief Rotate this Vector2 in radians.
	 *
	 * This only makes sense with a Vector2
	 *
	 * @param angle
	 * the angle to rotate on the Z-axis
	 */
	void rotate(T angle);
	/**
	 * @brief set the Rotation of this Vector2 in radians.
	 *
	 * This only makes sense with a Vector2
	 *
	 * @param angle
	 * the angle of rotation on the Z-axis
	 */
	void rotation(T angle);
	/**
	 * @brief Rotate this Vector2 in degrees.
	 *
	 * This only makes sense with a Vector2
	 *
	 * @param angle
	 * the angle to rotate on the Z-axis
	 */
	void rotateDeg(T angle);
	/**
	 * @brief set the Rotation of this Vector2 in degrees.
	 *
	 * This only makes sense with a Vector2
	 *
	 * @param angle
	 * the angle of rotation on the Z-axis
	 */
	void rotationDeg(T angle);
	/**
	 * @brief Get a rotated copy of this Vector2 in radians.
	 *
	 * This only makes sense with a Vector2
	 *
	 * @param angle
	 * the angle to rotate on the Z-axis
	 */
	const VectorX_t<T> getRotated(T angle) const;
	/**
	 * @brief Get a Rotated copy of this Vector2 in degrees.
	 *
	 * This only makes sense with a Vector2
	 *
	 * @param angle
	 * the angle to rotate on the Z-axis
	 */
	const VectorX_t<T> getRotatedDeg(T angle) const;
	/**
	 * @brief Limit the length of this Vector2 to the amount.
	 *
	 * @param amount
	 * the amount to limit to
	 */
	void limit(T amount);

	// operator overloaders
	/**
	 * @brief Overloads the < operator
	 *
	 * @param other
	 * The VectorX_t<T> to compare with (compares the length of the VectorX_t<T>)
	 *
	 * @return
	 * boolean. true if this VectorX_t is shorter than other
	 */
	bool operator<(VectorX_t<T> other);
	/**
	 * @brief Overloads the > operator
	 *
	 * @param other
	 * The VectorX_t<T> to compare with (compares the length of the VectorX_t<T>)
	 *
	 * @return
	 * boolean. true if this VectorX_t is longer than other
	 */
	bool operator>(VectorX_t<T> other);
	/**
	 * @brief Overloads the <= operator
	 *
	 * @param other
	 * The VectorX_t<T> to compare with (compares the length of the VectorX_t<T>)
	 *
	 * @return
	 * boolean. true if this VectorX_t is shorter or equal to other.
	 */
	bool operator<=(VectorX_t<T> other);
	/**
	 * @brief Overloads the >= operator
	 *
	 * @param other
	 * The VectorX_t<T> to compare with (compares the length of the VectorX_t<T>)
	 *
	 * @return
	 * boolean. true if this VectorX_t is longer or equal to other.
	 */
	bool operator>=(VectorX_t<T> other);
};

// =================================================
// Typedefs for VectorX_t<T>
// =================================================

/**
 * @brief A typedef for creating VectorX_t<int>
 *
 * Create a vector of ints
 *
 * @var Vector2i
 * A vector of ints
 */
typedef VectorX_t<int> Vector2i;
/**
 * @brief A typedef for creating VectorX_t<float>
 *
 * Create a vector of floats
 *
 * @var Vector2f
 * A vector of floats
 */
typedef VectorX_t<float> Vector2f;
/**
 * @brief A typedef for creating VectorX_t<double>
 *
 * Create a vector of doubles
 *
 * @var Vector2d
 * A vector of doubles
 */
typedef VectorX_t<double> Vector2d;
/**
 * @brief A typedef for creating a default Vector2
 *
 * Create a vector of floats. The default.
 *
 * @var Vector2
 * A vector of floats (default).
 */
typedef Vector2f Vector2;
/**
 * @brief A typedef for creating VectorX_t<int>
 *
 * Create a vector of ints
 *
 * @var Vector3i
 * A vector of ints
 */
typedef VectorX_t<int> Vector3i;
/**
 * @brief A typedef for creating VectorX_t<float>
 *
 * Create a vector of floats
 *
 * @var Vector3f
 * A vector of floats
 */
typedef VectorX_t<float> Vector3f;
/**
 * @brief A typedef for creating VectorX_t<double>
 *
 * Create a vector of doubles
 *
 * @var Vector3d
 * A vector of doubles
 */
typedef VectorX_t<double> Vector3d;
/**
 * @brief A typedef for creating a default Vector3
 *
 * Create a vector of floats. The default.
 *
 * @var Vector3
 * A vector of floats (default).
 */
typedef Vector3f Vector3;

// =================================================
// Implementation of VectorX_t<T>
// =================================================

// constructors and destructor
template <class T>
VectorX_t<T>::VectorX_t()
{

}

template <class T>
VectorX_t<T>::VectorX_t(T xx, T yy)
{
	this->x = xx;
	this->y = yy;
	this->z = 0;
}

template <class T>
VectorX_t<T>::VectorX_t(T xx, T yy, T zz)
{
	this->x = xx;
	this->y = yy;
	this->z = zz;
}

template <class T>
VectorX_t<T>::VectorX_t(Point_t<T> begin, Point_t<T> end)
{
    this->x = (end.x - begin.x);
    this->y = (end.y - begin.y);
    this->z = (end.z - begin.z);
}

template <class T>
VectorX_t<T>::VectorX_t(Point_t<T> p)
{
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
}

template <class T>
VectorX_t<T>::~VectorX_t()
{

}

// getLength()
template <class T>
const T VectorX_t<T>::getLength() const
{
	return sqrtf(getLengthSquared());
}

template <class T>
const T VectorX_t<T>::getLengthSquared() const
{
	T xx = this->x;
	T yy = this->y;
	T zz = this->z;

    return (xx*xx)+(yy*yy)+(zz*zz);
}

// setLength()
template <class T>
void VectorX_t<T>::setLength(T length)
{
	this->normalize();
	this->x *= length;
	this->y *= length;
}

// getAngle()
template <class T>
const T VectorX_t<T>::getAngle() const
{
	// this only works on a 2D Vector, so we use atan2()
	// because we want to know to which quadrant the Vector2 is pointing.
	// returns the angle relative to the X-axis.
	// range: -179.99 to +180
	return atan2(this->y, this->x);

	// You'd expect the following to work, but it doesn't, because the
	// angle between 2 Vectors is always between 0 and 180 degrees (pi radians)
	//return getAngle(VectorX_t<T>(1,0,0));
}

template <class T>
const T VectorX_t<T>::getAngleDeg() const
{
	return (getAngle() * RAD_TO_DEG);
}

// getAngle(VectorX_t<T>& other)
template <class T>
const T VectorX_t<T>::getAngle(const VectorX_t<T>& other) const
{
	VectorX_t<T> copy = *this;
	T dot = copy.dot(other);
	T l1 = copy.getLength();
	T l2 = other.getLength();

	return acos(dot/(l1*l2)); // law of cosines
}

template <class T>
const T VectorX_t<T>::getAngleDeg(const VectorX_t<T>& other) const
{
	return (getAngle(other) * RAD_TO_DEG);
}

// getNormalized() & normalize()
template <class T>
const VectorX_t<T> VectorX_t<T>::getNormalized() const
{
	VectorX_t<T> copy = *this;
	copy.normalize();

	return copy;
}

template <class T>
void VectorX_t<T>::normalize()
{
	T l = this->getLength();
	if (l != 0) {
		*this /= l;
	}
}

template <class T>
void VectorX_t<T>::lerp(T frac)
{
	*this *= frac;
}

template <class T>
const VectorX_t<T> VectorX_t<T>::getLerped(T frac) const
{
	VectorX_t<T> copy = *this;
	copy.lerp(frac);

	return copy;
}

// dot and cross products
template <class T>
const T VectorX_t<T>::dot(const VectorX_t<T>& other) const
{
	T x = this->x * other.x;
	T y = this->y * other.y;
	T z = this->z * other.z;

	return (x + y + z);
}

template <class T>
const VectorX_t<T> VectorX_t<T>::cross(const VectorX_t<T>& other) const
{
	T x = (this->y * other.z) - (this->z * other.y);
	T y = (this->z * other.x) - (this->x * other.z);
	T z = (this->x * other.y) - (this->y * other.x);

	return VectorX_t<T>(x,y,z);
}

// rotation
template <class T>
void VectorX_t<T>::rotate(T angle)
{
	T aa = this->getAngle() + angle;
	this->rotation(aa);
}

template <class T>
void VectorX_t<T>::rotation(T angle)
{
	T l = this->getLength();
	this->x = cos(angle) * l;
	this->y = sin(angle) * l;
}

template <class T>
void VectorX_t<T>::rotateDeg(T angle)
{
	this->rotate(angle * DEG_TO_RAD);
}

template <class T>
void VectorX_t<T>::rotationDeg(T angle)
{
	this->rotation(angle * DEG_TO_RAD);
}

template <class T>
const VectorX_t<T> VectorX_t<T>::getRotated(T angle) const
{
	VectorX_t<T> copy = *this;
	copy.rotate(angle);

	return copy;
}

template <class T>
const VectorX_t<T> VectorX_t<T>::getRotatedDeg(T angle) const
{
	return this->getRotated(angle * DEG_TO_RAD);
}

template <class T>
void VectorX_t<T>::limit(T amount)
{
	if (this->getLengthSquared() > amount*amount) {
		this->normalize();
		*this *= amount;
	}
}

// operator <, >, <=, >= overloader
template <class T>
bool VectorX_t<T>::operator<(VectorX_t<T> other)
{
	return (this->getLengthSquared() < other.getLengthSquared());
}

template <class T>
bool VectorX_t<T>::operator>(VectorX_t<T> other)
{
	return (this->getLengthSquared() > other.getLengthSquared());
}

template <class T>
bool VectorX_t<T>::operator<=(VectorX_t<T> other)
{
	return (this->getLengthSquared() <= other.getLengthSquared());
}

template <class T>
bool VectorX_t<T>::operator>=(VectorX_t<T> other)
{
	return (this->getLengthSquared() >= other.getLengthSquared());
}



// =================================================
// Class definition of Polar_t<T>
// =================================================
/// @brief Polar (to Cartesian) coordinates helper class
///
/// Usage:
/// @code
///   Vector2 vec = Vector2(4, 3);
///   std::cout << vec.getAngle()*RAD_TO_DEG << std::endl; // 36.8699
///   std::cout << vec.getLength() << std::endl; // 5.0
///
///   Polar p = Polar(36.8699*DEG_TO_RAD, 5.0f);
///   Vector2 velocity = p.cartesian();
///   std::cout << velocity << std::endl; // (4, 3)
/// @endcode
template <class T>
class Polar_t
{
public:
	T angle;	///< @brief angle of Polar_t
	T radius;	///< @brief radius of Polar_t

	/// @brief Default Polar_t<T> constructor.
	Polar_t<T>();
	/// @brief Overloaded Polar_t<T> constructor.
	/// @param a angle
	/// @param r radius
	Polar_t<T>(T a, T r);

	/// @brief Get the Cartesian coordinates of this Polar_t
	/// @return VectorX_t<T> A VectorX_t with the cartesian coordinates of this Polar_t
	const VectorX_t<T> cartesian() const;

	/// @brief Set this Polar from a VectorX_t
	/// @return Polar_t<T>
	Polar_t<T> fromCartesian(const VectorX_t<T>& vec);

	/// @brief Set this Polar from an x and y
	/// @return Polar_t<T>
	Polar_t<T> fromCartesian(T x, T y);
};

// =================================================
// Class implementation of Polar_t<T>
// =================================================
template <class T>
Polar_t<T>::Polar_t()
{
	this->angle = 0;
	this->radius = 1;
}

template <class T>
Polar_t<T>::Polar_t(T a, T r)
{
	this->angle = a;
	this->radius = r;
}

template <class T>
const VectorX_t<T> Polar_t<T>::cartesian() const
{
	VectorX_t<T> cartesian = VectorX_t<T>();

	cartesian.x = cos(this->angle) * this->radius;
	cartesian.y = sin(this->angle) * this->radius;
	cartesian.z = 0;

	return cartesian;
}

template <class T>
Polar_t<T> Polar_t<T>::fromCartesian(const VectorX_t<T>& vec)
{
	this->angle = vec.getAngle();
	this->radius = vec.getLength();

	return *this;
}

template <class T>
Polar_t<T> Polar_t<T>::fromCartesian(T x, T y)
{
	const VectorX_t<T> vec = VectorX_t<T>(x, y);

	return this->fromCartesian(vec);
}

/// @brief A typedef for creating a Polar of ints
typedef Polar_t<int> Polari;
/// @brief A typedef for creating a Polar of floats
typedef Polar_t<float> Polarf;
/// @brief A typedef for creating a Polar of doubles
typedef Polar_t<double> Polard;
/// @brief A typedef for creating a default Polar
typedef Polarf Polar;



#endif // VECTORX_H_
