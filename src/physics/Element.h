//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_ELEMENT_H
#define UNIPROJECT_ELEMENT_H

#include "Body.h"
#include "shapes/Shape.h"
#include "ElementListener.h"

class Element{
private:
	std::vector<ElementListener*> listeners;
public:
	Body &body;
	Shape* shape = nullptr;
	unsigned int filtertype;
	unsigned int filtercolliders;

	Element(Body &b, Shape *shape);
	void addListener(ElementListener *bodyListener);
	const std::vector<ElementListener*>& getListeners();
	~Element();

	void update();
};
#endif //UNIPROJECT_ELEMENT_H
