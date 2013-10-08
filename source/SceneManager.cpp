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
	SwapSceneState(SceneState::MAIN_MENU);
}

void SceneManager::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_mouseClicked)
{
	m_currentScene->Update(p_deltaTime, p_mousePositionX, p_mousePositionY, p_mouseClicked);
	
	SceneState::State l_sceneState = m_currentScene->GetSceneState();	
	if(l_sceneState != m_currentSceneState)
	{
		SwapSceneState(l_sceneState);
	}
}

void SceneManager::Render()
{
	m_currentScene->Render();
}

bool SceneManager::CheckIfExit()
{
	if(m_currentSceneState == SceneState::EXIT)
		return true;
	return false;
}

void SceneManager::SwapSceneState(SceneState::State p_sceneState)
{	
	int l_menuFlag;
	if(m_currentScene != 0) // Avoid crash during initialize
		l_menuFlag = m_currentScene->GetMenuFlag();

	if (p_sceneState == SceneState::MAIN_MENU)
	{
		SafeDelete(m_currentScene);
		m_currentScene = new MainMenuScene();
	}
	else if (p_sceneState == SceneState::GAME_MODE_MENU)
	{
		SafeDelete(m_currentScene);
		m_currentScene = new GameModeMenuScene();
	}
	else if (p_sceneState == SceneState::GAME)
	{
		SafeDelete(m_currentScene);
		m_currentScene = new GameScene(l_menuFlag);				// l_menuFlag represents what mode to start
	}
	else if (p_sceneState == SceneState::CAMPAIGNHIGHSCORE)
	{
		SafeDelete(m_currentScene);
		m_currentScene = new CampaignHighscoreScene(l_menuFlag); // l_menuFlag represents the score

	}
	else if (p_sceneState == SceneState::SURVIVALHIGHSCORE)
	{
		SafeDelete(m_currentScene);
		m_currentScene = new SurvivalHighscoreScene(l_menuFlag); // l_menuFlag represents the score
	}
	else if (p_sceneState == SceneState::EXIT)
		m_Exit = true;
	else
		return;
	m_currentScene->Initialize(m_renderComponentInterface);
	m_currentSceneState = p_sceneState;
}
