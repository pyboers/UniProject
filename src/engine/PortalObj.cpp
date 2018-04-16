//
// Created by Pierre-Yves Boers on 15/04/2018.
//

#include "PortalObj.h"




PortalObj::PortalObj(const Transform &transform, Mesh& mesh, Texture* texture) : Obj(transform, mesh, texture){

}

void PortalObj::bindPortal(PortalObj *bound) {
	this->bound = bound;
}
