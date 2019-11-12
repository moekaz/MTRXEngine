#include <PrecompiledHeader.h>
#include <math/Vector3D.h>

namespace mtrx
{
	// Setting up the zero vector
	Vector3D Vector3D::zero = Vector3D();

	// Constructor
	Vector3D::Vector3D(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// Destructor
	Vector3D::~Vector3D() {}

	/* Functions */

	// Normalization of a vector
	Vector3D Vector3D::Normalize()
	{
		// Maybe we can normalize by using the squares instead of the actual magnitude that would be faster runtime-wise 
		float mag = Magnitude();
		if (mag == 0) return *this;

		x = x / mag;
		y = y / mag;
		z = z / mag;

		return *this;
	}

	// Finding the magnitude of a vector
	float Vector3D::Magnitude()
	{
		return sqrt(MagnitudeSquared());
	}

	// Finding the magnitude squared of a vector
	float Vector3D::MagnitudeSquared()
	{
		// Square the x , y , z values add them up and return the result
		float xSquared = x * x;
		float ySquared = y * y;
		float zSquared = z * z;

		return xSquared + ySquared + zSquared;
	}

	// Finding the dot product between 2 vectors
	float Vector3D::DotProduct(Vector3D& v3d)
	{
		Vector3D vector = *this * v3d;
		return vector.x + vector.y + vector.z;
	}

	// Finding the cross product between 2 vectors
	Vector3D Vector3D::CrossProduct(Vector3D& v3d)
	{
		float i = (y * v3d.z) - (z * v3d.y);
		float j = (x * v3d.z) - (z * v3d.x);
		float k = (x * v3d.y) - (y * v3d.x);
		Vector3D cross = Vector3D(i, -j, k);
		return cross;
	}

	/* Operator overloading functions */

	Vector3D Vector3D::operator+(const Vector3D& v3d)
	{
		Vector3D newVector = Vector3D(x + v3d.x, y + v3d.y, z + v3d.z);
		return newVector;
	}

	Vector3D Vector3D::operator+(float f)
	{
		Vector3D newVector = Vector3D(x + f, y + f, z + f);
		return newVector;
	}

	Vector3D Vector3D::operator-(const Vector3D& v3d)
	{
		Vector3D newVector = Vector3D(x - v3d.x, y - v3d.y, z - v3d.z);
		return newVector;
	}

	Vector3D Vector3D::operator-(float f)
	{
		Vector3D newVector = Vector3D(x - f, y - f, z - f);
		return newVector;
	}

	// Negation of a vector
	Vector3D Vector3D::operator-()
	{
		return Vector3D(-x, -y, -z);
	}

	Vector3D Vector3D::operator*(const Vector3D& v3d)
	{
		Vector3D newVector = Vector3D(x * v3d.x, y * v3d.y, z * v3d.z);
		return newVector;
	}

	Vector3D Vector3D::operator*(float f)
	{
		Vector3D newVector = Vector3D(x * f, y * f, z * f);
		return newVector;
	}

	// Might need to check this 
	Vector3D Vector3D::operator/(const Vector3D& v3d)
	{
		// this might not work
		if (v3d.x == 0.0f || v3d.y == 0.0f || v3d.z == 0.0f) return NULL;

		Vector3D newVector = Vector3D(x / v3d.x, y / v3d.y, z / v3d.z);
		return newVector;
	}

	// Might need to check this
	Vector3D Vector3D::operator/(float f)
	{
		//might not work as well
		if (f == 0.0f) return NULL;
		Vector3D newVector = Vector3D(x / f, y / f, z / f);
		return newVector;
	}

	// Should this be void??
	Vector3D Vector3D::operator+=(const Vector3D& v3d)
	{
		*this = *this + v3d;
		return NULL;
	}

	// Should this be void??
	Vector3D Vector3D::operator+=(float f)
	{
		*this = *this + f;
		return NULL;
	}

	Vector3D Vector3D::operator-=(const Vector3D& v3d)
	{
		*this = *this - v3d;
		return NULL;
	}

	Vector3D Vector3D::operator-=(float f)
	{
		*this = *this - f;
		return NULL;
	}

	Vector3D Vector3D::operator*=(const Vector3D& v3d)
	{
		*this = *this * v3d;
		return NULL;
	}

	Vector3D Vector3D::operator*=(float f)
	{
		*this = *this * f;
		return NULL;
	}

	Vector3D Vector3D::operator/=(const Vector3D& v3d)
	{
		*this = *this / v3d;
		return NULL;
	}

	Vector3D Vector3D::operator/=(float f)
	{
		*this = *this / f;
		return NULL;
	}

	float Vector3D::operator[](int index)
	{
		if (index < 0 || index > 2) return NULL;
		return values[index];
	}

	// For consts
	float Vector3D::operator[](int index) const
	{
		return values[index];
	}

	// Checking for equality of vectors
	bool Vector3D::operator==(const Vector3D& vec)
	{
		return x == vec.x && y == vec.y && z == vec.z;
	}

	std::ostream& operator<<(std::ostream& os, const Vector3D& v3d)
	{
		os << "x: " << v3d.x << "\n"
			<< "y: " << v3d.y << "\n"
			<< "z: " << v3d.z;
		return os;
	}
}