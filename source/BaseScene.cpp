#include "BaseScene.h"


BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{

}

void BaseScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	m_renderComponentInterface = p_renderComponentInterface;
}

SceneState::State BaseScene::GetSceneState()
{
	return m_sceneState;
}

void BaseScene::ChangeCurrentState(SceneState::State l_sceneState, GameType::Type l_gameType)
{
	m_sceneState = l_sceneState;
	m_gameType = l_gameType;
}
