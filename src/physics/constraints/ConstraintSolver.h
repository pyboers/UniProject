//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_CONSTRAINTSOLVER_H
#define UNIPROJECT_CONSTRAINTSOLVER_H

#include <vector>
#include "Constraint.h"

class ConstraintSolver{
public:
	virtual void solve(std::vector<Constraint*>& constraints, float dt) = 0;
};
#endif //UNIPROJECT_CONSTRAINTSOLVER_H
