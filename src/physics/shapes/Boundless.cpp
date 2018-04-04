#include "Boundless.h"
#include <limits>

shapeType Boundless::getType() const
{
	return Type_BOUNDLESS;
}

void Boundless::update(vec3 position, quat rotation) {
	Shape::update(position, rotation);
}