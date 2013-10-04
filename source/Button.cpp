#include "Button.h"

Button::Button(BoundingBox p_boundingBox, 
					 BaseScene* p_scene, 
					 void (BaseScene::*p_function)(SceneState::State, GameType::Type), 
					 SceneState::State p_sceneState, 
					 GameType::Type p_gameType, 
					 RenderComponentInterface* p_renderComponentInterface, 
					 ButtonTexture p_buttonTexture)
{
	m_boundingBox = p_boundingBox;
	//m_boundingBox.Depth = -1;
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
//	l_coordinates.topRight =  m_boundingBox.PosX + m_boundingBox.Width;
//	l_coordinates.botLeft  =  ScreenStruct::Point()
//	l_coordinates.botRight =  m_boundingBox.PosX;


	BoundingBox l_boundingBox = m_renderComponentInterface->ConvertIntoScreenSpace(m_boundingBox, ENEMY1);

	/*
	if(	p_X > l_coordinates.topLeft.x && p_X < l_coordinates.topRight.x &&
		p_Y > l_coordinates.topLeft.y && p_Y < l_coordinates.topRight.y)
		return true;
	*/
	
	if(	p_X > l_boundingBox.PosX && p_X < l_boundingBox.PosX + l_boundingBox.Width &&
		p_Y > l_boundingBox.PosY && p_Y < l_boundingBox.PosY + l_boundingBox.Height)
	return true;
	

	return false;
}

void Button::ExecuteCommand()
{
	((m_scene)->*(m_function))(m_sceneState, m_gameType);
}

void Button::Render()
{
	m_renderComponentInterface->RenderObject(m_boundingBox, ENEMY1); 
	//m_renderComponentInterface->RenderObject(BoundingBox(m_boundingBox.PosX, m_boundingBox.PosY, m_boundingBox.Width, m_boundingBox.Height), ENEMY1); 
	//m_renderComponentInterface->RenderObject(BoundingBox(m_boundingBox.PosX, m_boundingBox.PosY, m_boundingBox.PosZ, m_boundingBox.Width, m_boundingBox.Height), ENEMY1); // with z
}