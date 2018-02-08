//
// Created by Pierre-Yves Boers on 07/02/2018.
//
#include "Transform.h"

Transform::Transform() : pos(0, 0, 0), rot(1, 0, 0, 0), scale(1), changed(changed) {}

Transform::Transform(vec3 pos) : pos(pos), rot(1, 0, 0, 1), scale(1), changed(true) {}

Transform::Transform(vec3 pos, vec3 scale) : pos(pos), rot(quat(1, 0, 0, 0)), scale(scale), changed(true){}

void Transform::rotate(vec3 axis, float angle, void * const subscriber) {
	this->rot = (quat(axis, angle) * rot).normalized();
	change(subscriber);
}

mat4 Transform::getMatrix() {
	static mat4 translationMatrix, rotationMatrix, scaleMatrix;
	translationMatrix.initTranslation(getPos());
	rotationMatrix.initRotation(rot);
	scaleMatrix.initScale(getScale());

	return translationMatrix * (rotationMatrix * (scaleMatrix));
}


const vec3 &Transform::getPos() {
	return pos;
}

Transform *Transform::setPos(const vec3 &pos, void * const subscriber) {
	this->pos = pos;
	change(subscriber);
	return this;
}

void Transform::addToPos(const vec3 &addVec, void * const subscriber) {
	setPos(getPos() + addVec, subscriber);
}

const quat &Transform::getRot() {
	return rot;
}

void Transform::setRot(const quat &rotation, void * const subscriber) {
	this->rot = rotation;
	change(subscriber);
}

const vec3 &Transform::getScale() {
	return scale;
}

void Transform::setScale(const vec3 &scale, void * const subscriber) {
	this->scale = scale;
	change(subscriber);
}

bool Transform::hasChanged(void *subscriber) {
	auto it = trackers.find(subscriber);
	if(it != trackers.end()){
		if(it->second){
			it->second = false;
			return true;
		}
	}else{
		return true;
	}
	return false;
}

void Transform::change(void *subscriber) {
	for (auto & s : trackers)
	{
		if(s.first != subscriber){
			s.second = true;
		}
	}


}
