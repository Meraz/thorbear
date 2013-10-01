#ifndef GAMEMODEMENUSCENE_H
#define GAMEMODEMENUSCENE_H

#include "BaseScene.h"

class GameModeMenuScene : public BaseScene
{
public:
	GameModeMenuScene();
	~GameModeMenuScene();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();

};

#endif