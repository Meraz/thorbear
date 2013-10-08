#ifndef GAMEMODEMENUSCENE_H
#define GAMEMODEMENUSCENE_H

#include <vector>
#include "BaseScene.h"
#include "Button.h"

class GameModeMenuScene : public BaseScene
{
public:
	GameModeMenuScene();
	~GameModeMenuScene();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
	void CheckButton(int p_mousePositionX, int p_mousePositionY);

private:
	std::vector<Button*> m_button;
};

#endif