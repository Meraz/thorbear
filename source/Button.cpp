#include "Button.h"

Button::Button(BoundingBox2D p_boundingBox, 
					 BaseScene* p_scene, 
					 void (BaseScene::*p_function)(SceneState::State, GameType::Type), 
					 SceneState::State p_sceneState, 
					 GameType::Type p_gameType, 
					 RenderComponentInterface* p_renderComponentInterface, 
					 ButtonTexture p_buttonTexture)
{
	m_boundingBox = p_boundingBox;
	m_scene = p_scene;
	m_function = p_function;
	m_sceneState = p_sceneState;
	m_gameType = p_gameType;
	m_renderComponentInterface = p_renderComponentInterface;
	m_buttonTexture = p_buttonTexture;
}

Button::~Button()
{
}

bool Button::CheckIfInside(int p_X, int p_Y)
{
	if(	p_X > m_boundingBox.PosX && p_X < m_boundingBox.PosX + m_boundingBox.Width &&
		p_Y > m_boundingBox.PosY && p_Y < m_boundingBox.PosY + m_boundingBox.Height)
		return true;
	return false;
}

void Button::ExecuteCommand()
{
	((m_scene)->*(m_function))(m_sceneState, m_gameType);
}

void Button::Render()
{
	//m_renderComponentInterface->RenderObject(BoundingBox(m_boundingBox.PosX, m_boundingBox.PosY, m_boundingBox.Width, m_boundingBox.Height), ENEMY1); // IT DOES NOT RENDER CORRECTLY
}
