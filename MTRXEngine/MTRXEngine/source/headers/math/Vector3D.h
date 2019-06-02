/*
    Author: Mohamed Kazma
    Description: An implementation of a 3D vector class whoch very benificial for game development
*/

#pragma once

namespace mtrx
{
	class Vector3D
	{
	public:
		/* Member variables */
		// Use a union to use either x y z values or an array for the values that way we can use regular vectors and also in arrays like matrices 
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float values[3];													// Array of 3 floats
		};

		static Vector3D zero;													// Some static zero vector that is used for default parameters and for lazy people who want a zero vector

		/* Constructors and Destructors */
		Vector3D(float x = 0, float y = 0, float z = 0);						// All unused variables will be set to 0
		~Vector3D();															// Destructor

		/* Functions */
		Vector3D Normalize();													// Normalizes a 3DVector
		float Magnitude();														// Finds the Magnitude of a 3DVector
		float MagnitudeSquared();												// Finds the Magnitude squared of a 3DVector
		float DotProduct(Vector3D&);											// Dot product of 2 3d vectors
		Vector3D CrossProduct(Vector3D&);										// Cross product of 2 3d vectors

		/* Operator overloading */
		friend std::ostream& operator<<(std::ostream&, const Vector3D&);		// Operator overloading to print out a 3d vector (just like a toString())
		Vector3D operator+(const Vector3D&);									// Adding 2 3d vectors
		Vector3D operator+(float);												// Adding a float to a 3d vector
		Vector3D operator+=(const Vector3D&);									// Adding 2 3d vectors using +=
		Vector3D operator+=(float);												// Adding a float to a 3d vector using +=
		Vector3D operator-(const Vector3D&);									// Subtracting 2 3d vectors
		Vector3D operator-(float);												// Subtracting a float from a 3d vector 
		Vector3D operator-=(const Vector3D&);									// Subtracting 2 3d vectors using -=
		Vector3D operator-=(float);												// Subtracting a float from a 3d vector using -= 
		Vector3D operator*(const Vector3D&);									// Multiplying 2 3d vectors
		Vector3D operator*(float);												// Multiplying a 3d vector by a float
		Vector3D operator*=(const Vector3D&);									// Multiplying 2 3d vectors using *=
		Vector3D operator*=(float);												// Multiplying a 3d vector by a float using *=
		Vector3D operator/(const Vector3D&);									// Dividing 2 3d vectors
		Vector3D operator/(float);												// Dividing a 3d vector by a float
		Vector3D operator/=(const Vector3D&);									// Dividing 2 3d vectors using /=
		Vector3D operator/=(float);												// Dividing a 3d vector by a float using /=
		float operator[](int);													// Get the values of the vector like an array
		float operator[](int) const;											// For consts
		bool operator == (const Vector3D&);										// Checking for equality between vectors
		Vector3D operator-();													// Negation of a 3d vector

	private:

	protected:
	};
}