//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_BINARYCONSTRAINT_H
#define UNIPROJECT_BINARYCONSTRAINT_H

#include "Constraint.h"
#include "../Element.h"

class BinaryConstraint : public Constraint{
protected:
	Element a, b;
};
#endif //UNIPROJECT_BINARYCONSTRAINT_H
