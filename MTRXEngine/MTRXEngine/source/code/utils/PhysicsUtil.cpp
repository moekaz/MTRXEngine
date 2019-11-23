/*
	Author: Mohamed Kazma
	Description: This will be a util file that will include some functions that a physics engine will generally need
	Implementation of smallest distance between 2 line segments:
		http://geomalgorithms.com/a07-_distance.html#dist3D_Segment_to_Segment
*/

#include <PrecompiledHeader.h>

#include <utils/PhysicsUtil.h>

namespace mtrx
{
	namespace PhysicsUtil
	{
		glm::vec3 TripleCross(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
		{
			// (A x B) x C = B(C . A) - A(C . B)
			return b * (glm::dot(c, a)) - a * (glm::dot(c, b));
		}

		float MinDistanceTwoLines(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D)
		{
			glm::vec3 l1 = B - A; // First direction vector
			glm::vec3 l2 = D - C; // Second direction vector

			glm::vec3 normalPlane = glm::fastNormalize(glm::cross(l1, l2));
			if (normalPlane == glm::vec3())
			{
				// They are parallel so choose any new vector that is not parallel to one of them and do
				// the cross product for that it should be parallel to both
				glm::vec3 newVec = l2 + glm::vec3(1, 1, 1);
				normalPlane = glm::cross(l1, newVec); // If the normal vector is (0,0,0) choose one of the 2
			}

			return std::abs(glm::dot(C - A, normalPlane));
		}

		float MinDistanceSquaredTwoSegments(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D)
		{
			glm::vec3 u = B - A;
			glm::vec3 v = D - C;
			glm::vec3 w = A - C;
			float a = glm::dot(u, u);
			float b = glm::dot(u, v);
			float c = glm::dot(v, v);
			float d = glm::dot(u, w);
			float e = glm::dot(v, w);
			float _D = a * c - b * b;
			float sc = 0, sn = 0;
			float sd = _D;
			float tc = 0, tn = 0;
			float td = _D;

			// Segments almost parallel
			if (_D < std::numeric_limits<float>::epsilon())
			{
				sn = 0.0f;
				sd = 1.0f;
				tn = e;
				td = c;
			}
			else
			{
				sn = b * e - c * d;
				tn = a * e - b * d;

				if (sn < 0.0f)
				{
					sn = 0.0;
					tn = e;
					td = c;
				}
				else if (sn > sd)
				{
					sn = sd;
					tn = e + b;
					td = c;
				}
			}

			if (tn < 0.0f)
			{
				tn = 0.0f;

				if (-d < 0.0f)
					sn = 0.0f;
				else if (-d > a)
					sn = sd;
				else
				{
					sn = -d;
					sd = a;
				}
			}
			else if (tn > td)
			{
				tn = td;

				if (-d + b < 0.0f)
					sn = 0.0f;
				else if (-d + b > a)
					sn = sd;
				else
				{
					sn = -d + b;
					sd = a;
				}
			}

			if (abs(sc) < std::numeric_limits<float>::epsilon())
				sc = 0;
			else
				sc = sn / sd; // Maybe this part is not checked
			if (abs(tc) < std::numeric_limits<float>::epsilon())
				tc = 0;
			else
				tc = tn / td; // Maybe this part is not checked as well

			glm::vec3 distanceVec = w + (u * sc) - (v * tc);
			return glm::dot(distanceVec, distanceVec);
		}

		std::pair<float, glm::vec3> MinDistanceSquaredPointSegment(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C)
		{
			glm::vec3 AB = B - A;
			glm::vec3 AC = C - A;
			glm::vec3 BC = C - B;

			float dot = glm::dot(AC, AB);
			if (dot < 0.0f)
			{
				return { glm::dot(AC, AC), A };	// Clamp to A being the closest point
			}
			else if (glm::dot(BC, AB) > 0.0f)
			{
				return { glm::dot(BC, BC), B };	// Clamp B to being the closest point
			}
			else
			{
				return { glm::dot(AC, AC) - (dot * dot), glm::fastNormalize(AB) * dot }; // Its a point between them so use pythagoras to find it
			}
		}

		std::pair<float, glm::vec3> MinDistanceSquaredPointRay(const glm::vec3& point, const glm::vec3& startPointRay, const glm::vec3& rayDirection)
		{
			// To keep the logic consistent
			glm::vec3 rayEndPt = startPointRay + (rayDirection * MAX_RAY_SIZE);
			return MinDistanceSquaredPointSegment(point, startPointRay, rayDirection);

			//float minDistance = 0;
			//glm::vec3 startPointToRay = point - startPointRay;

			//float dot = glm::dot(startPointToRay, rayDirection);
			//float distanceSquaredPointRay = glm::dot(startPointToRay, startPointToRay);
			//glm::vec3 closest;

			//if (dot < 0)
			//{
			//	minDistance = distanceSquaredPointRay;
			//	closest = startPointRay;	// Clamp on the starting point
			//}
			//else
			//{
			//	minDistance = distanceSquaredPointRay - (dot * dot);
			//	closest = glm::fastNormalize(rayDirection) * dot;	// Clamp onto the ray since it is infinite
			//}

			//return { minDistance, std::move(closest) };
		}

		float MinDistanceSquaredLineSegmentRay(const glm::vec3& a, const glm::vec3& b, const glm::vec3& rayStart, const glm::vec3& rayDirection)
		{
			return MinDistanceSquaredTwoSegments(a, b, rayStart, rayStart + (rayDirection * MAX_RAY_SIZE));
		}


		float MinDistanceSquaredPointTriangle(const glm::vec3& pt, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
		{
			glm::vec3 ab = b - a;
			glm::vec3 ac = c - a;

			glm::vec3 normal = glm::fastNormalize(glm::cross(ab, ac)); // Get the normal of the plane of the triangle
			glm::vec3 diff = pt - a; // Difference vector

			float dot = glm::dot(diff, normal);

			return glm::length2(diff - (dot * normal));
		}

		float MinDistanceSquaredLineSegmentTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, const glm::vec3& e)
		{
			std::array<const glm::vec3*, 3> tri = { &c, &d, &e };

			float minDistancSqr = -1.f;
			for (int i = 0; i < tri.size(); ++i)
			{
				int nextIndex = (i + 1) < tri.size() ? i + 1 : 0; // So that we don't use the modulo operation
				minDistancSqr = std::min(minDistancSqr, MinDistanceSquaredTwoSegments(a, b, *tri[i], *tri[nextIndex]));
			}

			return minDistancSqr;
		}

		std::pair<float, glm::vec3> MinDistanceSquaredPointAABB(const glm::vec3& pt, const glm::vec3& center, const float* halfExtents)
		{
			glm::vec3 closestPt = center;
			for (int i = 0; i < 3; ++i)
			{
				float min = center[i] - halfExtents[i];
				float max = center[i] + halfExtents[i];

				if (closestPt[i] < min)
					closestPt[i] = min;
				else if (closestPt[i] > max)
					closestPt[i] = max;
			}

			glm::vec3 diff = closestPt - center;
			return { glm::dot(diff, diff), closestPt };
		}

		glm::quat Slerp(const glm::quat& firstRotation, const glm::quat& secondRotation, float t)
		{
			if (t < 0 || t > 1) // If the value of t is off return the destination rotation
				return secondRotation;

			return glm::slerp(firstRotation, secondRotation, t);
		}

		glm::vec3 Lerp(const glm::vec3& startingPosition, const glm::vec3& destination, float t)
		{
			if (t < 0 || t > 1) // If the factor is wrong return the destination
				return destination;

			//return (1 - t) * startingPosition + t * destination;
			return startingPosition + (destination - startingPosition) * t;
		}

		float Ease(float t)
		{
			if (!t)
				return 1;

			return (float)(sin(t * PI - PI / 2.0f) + 1.0f) / 2.0f;
		}
	}
}