#pragma once
#ifndef IGA_C_BOUNDLESS_H
#define IGA_C_BOUNDLESS_H
#include "Shape.h"
#include "AABB.h"

class Boundless : public Shape {
public:


	shapeType getType() const override;


	void update(vec3 position, quat rotation) override;

	bool isPointInside(vec3 point) const;
};

#endif
