//
// Created by Pierre-Yves Boers on 03/02/2018.
//
#include "Shape.h"
#include "AABB.h"

/* AABB*/
static void calcCollisionInfo(const AABB &a1, const AABB &a2, vec3 **collisions, int *count){
	float sWidth = a1.getDimensions().getX() + a2.getDimensions().getX();
	float sHeight = a1.getDimensions().getY() + a2.getDimensions().getY();
	float sDepth = a1.getDimensions().getZ() + a2.getDimensions().getZ();
	float distancex = fabsf(a1.getPosition().getX() - a2.getPosition().getX());
	float distancey = fabsf(a1.getPosition().getY() - a2.getPosition().getY());;
	float distancez = fabsf(a1.getPosition().getZ() - a2.getPosition().getZ());;
	if(distancex < sWidth && distancey < sHeight && distancez < sDepth){ //collision
		if(distancex <= distancey && distancex <= distancez){ //X MTV
			if(a1.getPosition().getX() < a2.getPosition().getX()){
				*collisions = new vec3[3];
				*collisions[0] = vec3(distancex, 0, 0);
				*collisions[1] = vec3(-1, 0, 0);
				*collisions[2] = a1.getPosition();
				*count = 1;
			}else{
				*collisions = new vec3[3];
				*collisions[0] = vec3(-distancex, 0, 0);
				*collisions[1] = vec3(1, 0, 0);
				*collisions[2] = a1.getPosition();
				*count = 1;
			}
		}else if(distancey <= distancex && distancey <= distancez){ //Y MTV
			if(a1.getPosition().getY() < a2.getPosition().getY()){
				*collisions = new vec3[3];
				*collisions[0] = vec3(0, distancey, 0);
				*collisions[1] = vec3(0, -1, 0);
				*collisions[2] = a1.getPosition();
				*count = 1;
			}else{
				*collisions = new vec3[3];
				*collisions[0] = vec3(0, -distancey, 0);
				*collisions[1] = vec3(0, 1, 0);
				*collisions[2] = a1.getPosition();
				*count = 1;

			}
		}else{ //Z MTV
			if(a1.getPosition().getZ() < a2.getPosition().getZ()){
				*collisions = new vec3[3];
				*collisions[0] = vec3(0, 0, distancez);
				*collisions[1] = vec3(0, 0, -1);
				*collisions[2] = a1.getPosition();
				*count = 1;
			}else{
				*collisions = new vec3[3];
				*collisions[0] = vec3(0, 0, distancez);
				*collisions[1] = vec3(0, 0, 1);
				*collisions[2] = a1.getPosition();
				*count = 1;
			}
		}
		*count = 0;
	}
}