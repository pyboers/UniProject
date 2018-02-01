//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_ITERATIVESOLVER_H
#define UNIPROJECT_ITERATIVESOLVER_H

#include "ConstraintSolver.h"

class IterativeSolver: public ConstraintSolver{
protected:
	int solvercount;
public:
	IterativeSolver(int solvercount);
	void solve(std::vector<Constraint*>& constraints, float dt) override;
};
#endif //UNIPROJECT_ITERATIVESOLVER_H
