#include "BaseScene.h"


BaseScene::BaseScene()
{
	m_menuFlag = 0;
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

int BaseScene::GetMenuFlag()
{
	return m_menuFlag;
}

void BaseScene::ChangeCurrentState(SceneState::State l_sceneState, int l_menuFlag)
{
	m_sceneState = l_sceneState;
	m_menuFlag = l_menuFlag;
}
