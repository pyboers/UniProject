//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_ELEMENTLISTENER_H
#define UNIPROJECT_ELEMENTLISTENER_H

class Manifold;
class ElementListener{
public:
//	bool colliding;
	ElementListener(){}

//	void update(const Manifold& m, bool isA){
//		onCollide(m, isA);
//		if(colliding){
//			onCollideStart(m, isA);
//		}
//	}

	virtual bool onCollide(const Manifold& m, bool isA) = 0;
//	virtual bool onCollideStart(const Manifold& m, bool isA) = 0;
//	virtual bool onCollideEnd(const Manifold& m, bool isA) = 0;
};
#endif //UNIPROJECT_ELEMENTLISTENER_H
