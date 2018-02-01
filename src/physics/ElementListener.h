//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_ELEMENTLISTENER_H
#define UNIPROJECT_ELEMENTLISTENER_H

class Manifold;
class ElementListener{
public:
	ElementListener(){}

	virtual bool onCollide(const Manifold& m, bool isA) = 0;
};
#endif //UNIPROJECT_ELEMENTLISTENER_H
