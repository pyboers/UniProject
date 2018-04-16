//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_ELEMENTLISTENER_H
#define UNIPROJECT_ELEMENTLISTENER_H
#include <stdio.h>
#include <unordered_map>
class Element;
class Manifold;
class ElementListener{
private:
	std::unordered_map<Element*, int> collisions;
public:
	ElementListener(){

	}

	void update();

	bool onCollision(Manifold& m, bool isA);

	virtual bool onCollide(Manifold& m, bool isA) = 0;
	virtual bool onCollideStart(Manifold& m, bool isA) = 0;
};
#endif //UNIPROJECT_ELEMENTLISTENER_H
