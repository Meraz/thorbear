#include "Button.h"

Button::Button(
					BoundingBox p_boundingBox, 
					BaseScene* p_scene, 
					void (BaseScene::*p_function)(SceneState::State, int), 
					SceneState::State p_sceneState, 
					int p_menuFlag, 
					RenderComponentInterface* p_renderComponentInterface, 
					ButtonTexture p_buttonTexture)
{
	m_boundingBox = p_boundingBox;
	m_scene = p_scene;
	m_function = p_function;
	m_sceneState = p_sceneState;
	m_menuFlag = p_menuFlag;
	m_renderComponentInterface = p_renderComponentInterface;
	m_buttonTexture = p_buttonTexture;
}

Button::~Button()
{
}

bool Button::CheckIfInside(int p_X, int p_Y)
{
	BoundingBox l_boundingBox = m_renderComponentInterface->ConvertIntoScreenSpace(m_boundingBox, ENEMY1);
	
	if(	p_X > l_boundingBox.PosX && p_X < l_boundingBox.PosX + l_boundingBox.Width &&
		p_Y > l_boundingBox.PosY && p_Y < l_boundingBox.PosY + l_boundingBox.Height)
	return true;	

	return false;
}

void Button::ExecuteCommand()
{
	((m_scene)->*(m_function))(m_sceneState, m_menuFlag);
}

void Button::Render()
{
	m_renderComponentInterface->RenderObject(m_boundingBox, ENEMY1); 
}