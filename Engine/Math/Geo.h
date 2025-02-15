#pragma once

#include "Vector.h"

namespace Geo
{
	/**
	 * Transforms a 3D vector into a 2D vector using a transformation matrix and screen dimensions.
	 *
	 * @param v3 The input 3D vector to be transformed.
	 * @param v2 The output 2D vector resulting from the transformation.
	 * @param m A 4x4 transformation matrix used for the projection.
	 * @param sd The space dimensions, defaulting to empty.
	 * @return True if the transformation is successful and the vector is within view; false otherwise.
	 */
	bool Get2DVector(const Vector3 &v3, Position &v2, const float m[16], const Dimension &sd = {0, 0})
	{
		Vector4 clipCoords;
		clipCoords.x = v3.x * m[0] + v3.y * m[1] + v3.z * m[2] + m[3];
		clipCoords.y = v3.x * m[4] + v3.y * m[5] + v3.z * m[6] + m[7];
		clipCoords.z = v3.x * m[8] + v3.y * m[9] + v3.z * m[10] + m[11];
		clipCoords.w = v3.x * m[12] + v3.y * m[13] + v3.z * m[14] + m[15];

		if (clipCoords.w < 0.1f)
			return false;

		Vector3 coords;
		coords.x = clipCoords.x / clipCoords.w;
		coords.y = clipCoords.y / clipCoords.w;
		coords.z = clipCoords.z / clipCoords.w;

		const float W2 = sd.w / 2;
		const float H2 = sd.h / 2;

		v2.x = (W2 * coords.x) + coords.x + W2;
		v2.y = -(H2 * coords.y) + coords.y + H2;

		return true;
	}

	float GetVectorDistance(const Vector3 &p1, const Vector3 &p2)
	{
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.x - p2.x, 2) + pow(p1.z - p2.z, 2));
	}
};
