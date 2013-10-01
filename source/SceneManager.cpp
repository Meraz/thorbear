#include "SceneManager.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	SafeDelete(m_currentScene);
}

void SceneManager::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	m_renderComponentInterface = p_renderComponentInterface;

	m_currentScene = 0;
	SwapSceneState(GAME);
}

bool SceneManager::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
	m_currentScene->Update(p_deltaTime, p_mousePositionX, p_mousePositionY, p_lMouseClicked);
	
	SceneState l_sceneState = m_currentScene->GetSceneState();	
	if(l_sceneState != m_currentSceneState)
	{
		SwapSceneState(l_sceneState);
		return false;
	}
	return true;
}

void SceneManager::Render()
{
	m_currentScene->Render();
}

bool SceneManager::CheckIfExit()
{
	if(m_currentSceneState == EXIT)
		return true;
	return false;
}

void SceneManager::SwapSceneState(SceneState p_sceneState)
{	
	if (p_sceneState == MENU)
	{
		SafeDelete(m_currentScene);
		m_currentScene = new MenuScene();
	}
	else if (p_sceneState == GAME)
	{
		SafeDelete(m_currentScene);
		m_currentScene = new GameScene();
	}
	else if (p_sceneState == HIGHSCORE)
	{
		SafeDelete(m_currentScene);
		m_currentScene = new HighScoreScene();
	}
	else if (p_sceneState == EXIT)
		m_Exit = true;
	else
		return;
	m_currentScene->Initialize(m_renderComponentInterface);
	m_currentSceneState = p_sceneState;
}
