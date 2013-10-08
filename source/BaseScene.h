#ifndef BASESCENE_H
#define BASESCENE_H

#include "RenderComponentInterface.h"
#include "SceneState.h"
#include "GameType.h"

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Initialize(RenderComponentInterface* p_renderComponentInterface);
	virtual void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked) = 0;
	virtual void Render() = 0;
	virtual SceneState::State GetSceneState();
	
protected:
	virtual void ChangeCurrentState(SceneState::State l_sceneState, GameType::Type l_gameType);


protected:
	RenderComponentInterface* m_renderComponentInterface;
	SceneState::State m_sceneState;
	 GameType::Type m_gameType;			// Used to start the game with different parameters.

};

#endif