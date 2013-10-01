#ifndef BASESCENE_H
#define BASESCENE_H

enum SceneState
{
	Menu,
	GAME,
	HIGHSCORE,
	EXIT
};

#include "RenderComponentInterface.h"

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Initialize(RenderComponentInterface* p_renderComponentInterface);
	virtual void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked) = 0;
	virtual void Render() = 0;
	virtual SceneState GetSceneState();
	
protected:

protected:
	RenderComponentInterface* m_renderComponentInterface;
	SceneState m_sceneState;

};

#endif