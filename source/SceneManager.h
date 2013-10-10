#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "GameInterface.h"
#include "BaseScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "GameModeMenuScene.h"
#include "CampaignHighScoreScene.h"
#include "SurvivalHighscoreScene.h"
#include "MemoryMacro.h"
#include "SoundHandler.h"

class SceneManager : public GameInterface 
{
public:
	SceneManager();
	~SceneManager();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_mouseClicked);
	void Render();
	bool CheckIfExit();

private:
	void SwapSceneState(SceneState::State p_sceneState);

private:
	RenderComponentInterface* m_renderComponentInterface;

	SceneState::State m_currentSceneState;
	BaseScene* m_currentScene;
	SoundHandler* m_soundHandler;
	bool m_Exit;

};

#endif