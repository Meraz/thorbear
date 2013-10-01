#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "BaseScene.h"


class MenuScene : public BaseScene
{
public:
	MenuScene();
	~MenuScene();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
};

#endif