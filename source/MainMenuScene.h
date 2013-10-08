#ifndef MAIMMENUSCENE_H
#define MAIMMENUSCENE_H

#include <vector>
#include "BaseScene.h"
#include "Button.h"
#include "GameType.h"

class MainMenuScene : public BaseScene
{
public:
	MainMenuScene();
	~MainMenuScene();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
	void CheckButton(int p_mousePositionX, int p_mousePositionY);

protected:


private:
	void SwapToGame();

private:
	std::vector<Button*> m_button;
};

#endif