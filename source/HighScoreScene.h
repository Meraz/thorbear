#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H

#include "BaseScene.h"


class HighScoreScene : public BaseScene
{
public:
	HighScoreScene();
	~HighScoreScene();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
	int a; // TODO : Remove this. Test code

};

#endif