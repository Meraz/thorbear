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

SceneState BaseScene::GetSceneState()
{
	return m_sceneState;
}