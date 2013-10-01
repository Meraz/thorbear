#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "GameInterface.h"
#include "BaseScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "GameModeMenuScene.h"
#include "HighScoreScene.h"
#include "MemoryMacro.h"

class SceneManager : public GameInterface 
{
public:
	SceneManager();
	~SceneManager();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	bool Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
	bool CheckIfExit();

private:
	void SwapSceneState(SceneState::State p_sceneState);


private:
	RenderComponentInterface* m_renderComponentInterface;

	SceneState::State m_currentSceneState;
	BaseScene* m_currentScene;

	bool m_Exit;

};

#endif