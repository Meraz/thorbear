#ifndef GAME_H
#define GAME_H

#include "GameInterface.h"

class Game : public GameInterface
{
public:
	Game();
	virtual ~Game();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY /* add keyboard parameters here*/); // TODO add vector with keyclicks here
	void Render();

private:

private:
	RenderComponentInterface* m_renderComponentInterface;
};

#endif