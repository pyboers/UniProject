#pragma once

#ifndef __MYMATH_H
#define __MYMATH_H

#include <math.h>
#include <stdlib.h>

#define PI 3.141592653589793238463
#define PI_F 3.14159265358979f

// Converts degrees to radians.
#define degreesToRadians_F(degrees) (degrees * PI_F / 180.0f)

// Converts radians to degrees.
#define radiansToDegrees_F(radians) (radians * 180.0f / PI_F)

// Converts degrees to radians.
#define degreesToRadians(degrees) (degrees * PI / 180.0f)

// Converts radians to degrees.
#define radiansToDegrees(radians) (radians * 180.0f / PI)

namespace math {

	/**
	 * Returns a random float between min and max.
	 *
	 * @param min Minimum possible value
	 * @param max Maximum possible value
	 * @param r   Random object
	 * @return A random float between min and max
	 */
	static float getRandom(float min, float max) {
		return min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
	}

	/**
	 * Calculates the remainder.
	 *
	 * @param x first int
	 * @param y second int
	 * @return remainder
	 */
	static int getRemainder(int x, int y) {
		int i = x % y;
		if (i < 0) {
			i += y;
		}
		return i;
	}

	/**
	 * returns the distance.
	 */
	static float distance(float x1, float y1, float x2, float y2) {
		return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}

	/**
	 * Returns the distance squared.
	 */
	static float sdistance(float x1, float y1, float x2, float y2) {
		return ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));
	}


	/**
	 * Returns the signed area of a triangle specified by the input coordinates.
	 */
	static float areaTri(float ax, float ay, float bx, float by, float cx, float cy) {
		return ((ax * (by - cy)) + (bx * (cy - ay)) + (cx * (ay - by))) / 2;
	}

	/**
	 * Returns the area of a triangle.
	 */
	static float areaTriA(float ax, float ay, float bx, float by, float cx, float cy) {
		return fabsf((ax * (by - cy)) + (bx * (cy - ay)) + (cx * (ay - by))) / 2;
	}

    /**
* Tests to see if a point is inside or touching the triangle.
*
* @param ax X coordinate of vertex a
* @param ay Y coordinate of vertex a
* @param bx X coordinate of vertex b
* @param by Y coordinate of vertex b
* @param cx X coordinate of vertex c
* @param cy Y coordinate of vertex c
* @param x  X coordinate of point
* @param y  Y coordinate of point
* @return true if the point is touching or inside the triangle
*/
    static bool isPointInsideOrTouchingTriangle(float ax, float ay, float bx, float by, float cx, float cy,
                                                float x, float y) {
        float area1 = areaTri(ax, ay, x, y, bx, by);
        float area2 = areaTri(bx, by, x, y, cx, cy);
        float area3 = areaTri(cx, cy, x, y, ax, ay);
        return area1 >= 0 && area2 >= 0 && area3 >= 0;
    }

/**
* Tests to see if a point is inside the triangle.
*
* @param ax X coordinate of vertex a
* @param ay Y coordinate of vertex a
* @param bx X coordinate of vertex b
* @param by Y coordinate of vertex b
* @param cx X coordinate of vertex c
* @param cy Y coordinate of vertex c
* @param x  X coordinate of point
* @param y  Y coordinate of point
* @return true if the point is inside the triangle
*/
    static bool isPointInsideTriangle(float ax, float ay, float bx, float by, float cx, float cy, float x,
                                      float y) {
        float area1 = areaTri(ax, ay, x, y, bx, by);
        float area2 = areaTri(bx, by, x, y, cx, cy);
        float area3 = areaTri(cx, cy, x, y, ax, ay);
        return area1 > 0 && area2 > 0 && area3 > 0;
    }


	/**
	 * Return the value of x with a lower bound of min and an upper bound of max.
	 *
	 * @param x   Value to be clamped
	 * @param min Minimum value
	 * @param max Maximum value
	 * @return min when x is less than min, max when x is more than max, x when x is between min and max
	 */
	static float clamp(float x, float min, float max) {
		if (x < min) {
			return min;
		}
		if (x > max) {
			return max;
		}
		return x;
	}

}

#endif