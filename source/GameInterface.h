#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H
#include "RenderComponentInterface.h"

class GameInterface
{
public:
	virtual void Initialize(RenderComponentInterface* p_renderComponentInterface) = 0;
	virtual void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked /* add keyboard parameters here*/) = 0;	// TODO add vector with keyclicks here
	virtual void Render() = 0;
	virtual bool CheckIfExit() = 0;
	virtual ~GameInterface() {}
};

#endif 