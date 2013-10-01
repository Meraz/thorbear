#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "GameInterface.h"
#include "BaseScene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "HighScoreScene.h"
#include "MemoryMacro.h"

class SceneManager : public GameInterface 
{
public:
	SceneManager();
	~SceneManager();

	void Initialize(RenderComponentInterface* p_renderComponentInterface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
	bool CheckIfExit();

private:
	void SwapSceneState(SceneState p_sceneState);


private:
	RenderComponentInterface* m_renderComponentInterface;

	SceneState m_currentSceneState;
	BaseScene* m_currentScene;
	GameScene* m_gameScene;
	MenuScene* m_menuScene;
	HighScoreScene* m_highScoreScene;

	bool m_Exit;

};

#endif