//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_COLLISIONDETECTOR_H
#define UNIPROJECT_COLLISIONDETECTOR_H

#include "Manifold.h"

class CollisionDetector{
protected:
	std::vector<Body*>& bodies;
	virtual Manifold* detectCollision(Element &a, Element &b){
		bool solve = (((a.filtertype & b.filtercolliders) != 0) && (a.body.inv_Mass != 0 || b.body.inv_Mass != 0) && ((a.filtercolliders & b.filtertype) !=0));
		if(solve){
			vec3 * collisioninfo;
			int count = 0;
			Shape::getCollisionInfo(a.shape, b.shape, &collisioninfo, &count);

			if(count > 0){
				Manifold *m = new Manifold(a, b, collisioninfo, count);
				for(ElementListener *elementListener : a.getListeners()){
					solve &= elementListener->onCollide(*m, true);
				}
				for(ElementListener *elementListener : b.getListeners()){
					solve &= elementListener->onCollide(*m, false);
				}
				if(solve){
					delete[] collisioninfo;
					return m;
				}
				delete[] collisioninfo;
			}
		}
		return nullptr;
	}
public:
	explicit CollisionDetector(std::vector<Body*>& bodies) : bodies(bodies){}

	virtual Manifold* detectCollisions() = 0;
};
#endif //UNIPROJECT_COLLISIONDETECTOR_H
