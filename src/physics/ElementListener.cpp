//
// Created by Pierre-Yves Boers on 17/04/2018.
//
#include "Element.h"
#include "constraints/manifold/Manifold.h"

void ElementListener::update() {
	for(auto& collision : collisions){
		collision.second--;
	}
	for (auto it = collisions.begin(); it != collisions.end();) {
		if(it->second < 0) {
			it = collisions.erase(it);
		} else{
			it++;
		}
	}
}

bool ElementListener::onCollision(Manifold &m, bool isA) {
	Element& other = isA ? m.b : m.a;
	auto col = collisions.find(&other);
	if(col == collisions.end()){
		collisions.insert({&other, 1});
		return onCollideStart(m, isA);
	}
	collisions.erase(&other);
	collisions.insert({&other, 1});
	return onCollide(m, isA);

}
