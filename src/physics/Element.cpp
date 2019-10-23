//
// Created by Pierre-Yves Boers on 03/04/2018.
//
#include "Element.h"
#include "Body.h"
Element::Element(Body &b, Shape *shape) : body(b), shape(shape){
	filtertype = 1;
	filtercolliders = ALLCOLLIDER;
	update();
}

void Element::addListener(ElementListener *bodyListener) {
	listeners.push_back(bodyListener);
}

const std::vector<ElementListener *> &Element::getListeners() {
	return listeners;
}

Element::~Element() {
	delete shape;
}

void Element::update() {
	shape->update(body.position, body.orientation);
}
