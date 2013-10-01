#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H

#include <vector>

#include "BaseScene.h"
#include "Button.h"

class HighScoreScene : public BaseScene
{
public:
	HighScoreScene();
	~HighScoreScene();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
	void CheckButton(int p_mousePositionX, int p_mousePositionY);

private:
	std::vector<Button*> m_button;
};

#endif