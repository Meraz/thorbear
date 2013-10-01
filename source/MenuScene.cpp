#include "MenuScene.h"


MenuScene::MenuScene(void)
{
}


MenuScene::~MenuScene(void)
{
}

void MenuScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	BaseScene::Initialize(p_renderComponentInterface);
	m_sceneState = Menu;
}


void MenuScene::Update( double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked )
{

}

void MenuScene::Render()
{

}