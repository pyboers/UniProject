//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_CONSTRAINT_H
#define UNIPROJECT_CONSTRAINT_H
class Constraint{

public:

	virtual void update(float dt) = 0;
	virtual void solve(float dt) = 0;
};
#endif //UNIPROJECT_CONSTRAINT_H
