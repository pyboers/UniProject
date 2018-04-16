//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_AABB_H
#define UNIPROJECT_AABB_H

#include "Shape.h"

/**
 * Axis-Aligned-Bounding-Box
 */
class AABB : public Shape{
protected:
	vec3 dimensions;

public:
	AABB(vec3 position, vec3 dimensions);

	shapeType getType() const override;

	const vec3 &getDimensions() const;

	bool isPointInside(vec3 point) const override;
};
#endif //UNIPROJECT_AABB_H
