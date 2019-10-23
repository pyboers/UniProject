//
// Created by Pierre-Yves Boers on 16/04/2018.
//

#ifndef UNIPROJECT_PORTALCOLLISIONLISTENER_H
#define UNIPROJECT_PORTALCOLLISIONLISTENER_H


#include "../physics/ElementListener.h"

class PortalCollisionListener : public ElementListener{

	bool onCollide(Manifold& m, bool isA) override;
	bool onCollideStart(Manifold& m, bool isA) override;
};


#endif //UNIPROJECT_PORTALCOLLISIONLISTENER_H
