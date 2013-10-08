#ifndef BASESCENE_H
#define BASESCENE_H

#include "RenderComponentInterface.h"
#include "SceneState.h"
#include "GameType.h"

#define START_CAMPAIGN 1
#define START_SURVIVAL 2

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Initialize(RenderComponentInterface* p_renderComponentInterface);
	virtual void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked) = 0;
	virtual void Render() = 0;
	SceneState::State GetSceneState();
	int GetMenuFlag();
	
protected:
	virtual void ChangeCurrentState(SceneState::State l_sceneState, int l_menuFlag);
	void RenderParticleEffect(int p_x, int p_z);

protected:
	RenderComponentInterface* m_renderComponentInterface;
	SceneState::State m_sceneState;
	int m_menuFlag;		// Used to start the game with different parameters.
	bool m_previousMouseState;

};

#endif