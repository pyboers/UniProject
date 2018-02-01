//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_ELEMENT_H
#define UNIPROJECT_ELEMENT_H

#include "Body.h"
#include "Shape.h"

class Element{
	Body &body;
	Shape* shape = nullptr;
	unsigned int filtertype;
	unsigned int filtercolliders;

	Element(Body &b, Shape *shape);
	~Element();

	void update();
};
#endif //UNIPROJECT_ELEMENT_H
