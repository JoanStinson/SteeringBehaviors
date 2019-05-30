/* ========================================================================
   File: Vector2D.h
   Revision: 0.1
   Creator: David Collado Ochoa
   Notice: (C) Copyright 2016 by David Collado Ochoa. All Rights Reserved.
   ======================================================================== */

#pragma once

#include <math.h>

#ifndef M_PI	
#define M_PI	3.14159265358979323846   // pi
#endif

#define RAD2DEG (180.0f / (float)M_PI)
#define DEG2RAD ((float)M_PI / 180.0f)

struct Vector2D
{
	float x = 0.0f;
	float y = 0.0f;
	
	Vector2D(float valueX = 0.0f, float valueY = 0.0f): x{valueX}, y{valueY}
	{}
	
	inline float Length() const
	{
		return (float)sqrt(x * x + y * y);
	}

	inline float LengthSquared() const
	{
		return x * x + y * y;
	}
	
	inline Vector2D operator+(const Vector2D& v)
	{
		return Vector2D(x + v.x, y + v.y);
	}
	inline void operator+=(const Vector2D& v2)
	{
		x += v2.x;
		y += v2.y;
	}
	
	inline Vector2D operator-(const Vector2D& v)
	{
		return Vector2D(x - v.x, y - v.y);
	}
	inline void operator-=(const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
	}
	
	inline Vector2D operator*(float scalar)
	{
		return Vector2D(x * scalar, y * scalar);
	}
	inline void operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
	}
	
	inline Vector2D operator/(float scalar)
	{
		return Vector2D(x / scalar, y / scalar);
	}
	inline void operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
	}

	inline bool operator==(const Vector2D& rhs) const
	{
		return (x == rhs.x)
			&& (y == rhs.y);
	}
	inline bool operator!=(const Vector2D& rhs) const
	{
		return !operator==(rhs);
	}
	
	inline Vector2D Normalize()
	{
		float l = Length();
		if ( l > 0.0f)
		{
			(*this) *= 1.0f / l;
		}
		return (*this);
	}
	static inline Vector2D Normalize(const Vector2D& v)
	{
		float l = v.Length();
		if ( l > 0.0f)
		{
			return Vector2D(v.x / l, v.y/ l);
		}
		else
		{
			return Vector2D();
		}
	}

	static inline float Dot(const Vector2D& v1, const Vector2D& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline Vector2D Truncate(float max)
	{
		if (Length() > max)
		{
			(*this) = (*this).Normalize() * max;
		}

		return (*this);
	}
	static inline Vector2D Truncate(const Vector2D& v, float max)
	{
		Vector2D truncated = Vector2D(v.x, v.y);
		if (v.Length() > max)
		{
			truncated = truncated.Normalize() * max;
		}
		return truncated;
	}

	static inline float Distance(Vector2D start, Vector2D end)
	{
		Vector2D v = start - end;
		return v.Length();
	}

	static inline float DistanceSquared(Vector2D start, Vector2D end)
	{
		Vector2D v = start - end;
		return v.LengthSquared();
	}
};

namespace Vector2DUtils
{
	static Vector2D GetClosestPoint(Vector2D start, Vector2D end, Vector2D point)
	{
		Vector2D startToPoint = { point.x - start.x, point.y - start.y };
		Vector2D startToEnd = { end.x - start.x, end.y - start.y };

		// Finding the squared magnitude of startToEnd
		float startToEndSquaredMag = startToEnd.x * startToEnd.x + startToEnd.y * startToEnd.y;

		// The dot product of startToEnd and startToPoint
		float dotProduct = startToPoint.x * startToEnd.x + startToPoint.y * startToEnd.y;

		// The normalized "distance" from start to closest point
		float t = dotProduct / startToEndSquaredMag;

		if (t < 0.0)
		{
			return start; // Beyond the 'start' end of the segment
		}

		else if (t > 1.0)
		{
			return end;  // Beyond the 'end' end of the segment
		}
		else
		{
			// Add the distance to start, moving towards end
			Vector2D nearestPoint = { start.x + startToEnd.x * t,  start.y + startToEnd.y * t };
			return nearestPoint;
		}
	}

	static bool IsInsideCone(Vector2D point, Vector2D coneApex, Vector2D coneBase, float coneHalfAngle)
	{
		Vector2D apexToPoint = point - coneApex;
		Vector2D axisVect = coneBase - coneApex;

		// Point is inside cone only if it's lying in 
		// infinite version of its cone.
		// We'll use Dot() to 
		// determine angle between apexToPoint and axisVect.
		bool isInInfiniteCone = (Vector2D::Dot(apexToPoint, axisVect) / 
			(apexToPoint.Length() * axisVect.Length())) > cosf(coneHalfAngle * (float)DEG2RAD);

		if (!isInInfiniteCone)
		{
			return false;
		}

		// Point is contained in cone only if projection of apexToPoint to axisVect
		// is shorter than axisVect. 
		// We'll use Dot() to figure scalar projection length.
		bool isInsideCone = (Vector2D::Dot(apexToPoint, axisVect) / axisVect.Length()) < axisVect.Length();
		return isInsideCone;
	}

	static Vector2D RotatePoint(Vector2D center, Vector2D point, float angle)
	{
		float s = sinf(angle * DEG2RAD);
		float c = cosf(angle * DEG2RAD);

		// Translate point back to origin
		point.x -= center.x;
		point.y -= center.y;

		// Rotate point
		float newX = point.x * c - point.y * s;
		float newY = point.x * s + point.y * c;

		// Translate point back
		point.x = newX + center.x;
		point.y = newY + center.y;
		return point;
	}

	// s1_start is line1 start, s1_end is line1 end, s2_start is line2 start, s2_end is line2 end
	static bool SegmentSegmentIntersection(Vector2D s1_start, Vector2D s1_end, Vector2D s2_start, Vector2D s2_end, 
		bool doIntersectOnPoints = true, Vector2D* intersectionPoint = nullptr)
	{
		intersectionPoint = {};
		Vector2D r = s1_end - s1_start;
		Vector2D s = s2_end - s2_start;
		float rCrossS = r.x * s.y - r.y * s.x;

		// if r cross s == 0, it means the lines are parallel so have infinite intersection points
		if (rCrossS == 0)
		{
			return false;
		}

		Vector2D c = s2_start - s1_start;
		float t = (c.x * s.y - c.y * s.x) / rCrossS;
		// If it is equal, no intersection
		if (doIntersectOnPoints)
		{
			if (t < 0 || t > 1)
			{
				return false;
			}
		}
		else
		{
			if (t <= 0 || t >= 1)
			{
				return false;
			}
		}

		float u = (c.x * r.y - c.y * r.x) / rCrossS;
		// If it is equal, no intersection
		if (doIntersectOnPoints)
		{
			if (u < 0 || u > 1)
			{
				return false;
			}
		}
		else
		{
			if (u <= 0 || u >= 1)
			{
				return false;
			}
		}


		if (intersectionPoint != nullptr)
		{
			*intersectionPoint = s1_start + r * t;
		}

		return true;
	}

	static float PointDirection(Vector2D p1, Vector2D p2)
	{
		Vector2D P12 = p2 - p1;
		return (float)atan2(P12.y, P12.x) * RAD2DEG;
	}
}
