//
// Created by Pierre-Yves Boers on 10/02/2018.
//
#include "IterativeSolver.h"

IterativeSolver::IterativeSolver(int solvercount) : solvercount(solvercount){

}

void IterativeSolver::solve(std::vector<Constraint *> &constraints, float dt) {
	for(auto& c : constraints){
		c->update(dt);
	}
	for(int i = 0; i < solvercount; i++){
		for(auto& c : constraints){
			c->solve(dt);
		}
	}
}
