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
	m_constructorId = 0;
	m_clickable = new bool(true);
}

Button::Button( BoundingBox p_boundingBox, Highscore* p_highscore, void (Highscore::*p_function)(int), int p_buttonId, RenderComponentInterface* p_renderComponentInterface, ButtonTexture p_buttonTexture )
{
	m_boundingBox = p_boundingBox;
	m_highscore = p_highscore;
	m_functionCharChange = p_function;
	m_buttonId = p_buttonId;
	m_renderComponentInterface = p_renderComponentInterface;
	m_buttonTexture = p_buttonTexture;
	m_constructorId = 1;
	m_clickable = p_highscore->GetnewAdditionToHighscorePointer();
}

Button::Button( BoundingBox p_boundingBox, Highscore* p_highscore, void (Highscore::*p_function)(), RenderComponentInterface* p_renderComponentInterface, ButtonTexture p_buttonTexture )
{
	m_boundingBox = p_boundingBox;
	m_highscore = p_highscore;
	m_functionSave = p_function;
	m_renderComponentInterface = p_renderComponentInterface;
	m_buttonTexture = p_buttonTexture;
	m_constructorId = 2;
	m_clickable = p_highscore->GetnewAdditionToHighscorePointer();
}

Button::~Button()
{
	if(m_constructorId == 0)
		 SafeDelete(m_clickable);
}

bool Button::CheckIfInside(int p_X, int p_Y)
{
	if(*m_clickable == false)
		return false;

	BoundingBox l_boundingBox = m_renderComponentInterface->ConvertIntoScreenSpace(m_boundingBox, ENEMY1);
	
	if(	p_X > l_boundingBox.PosX && p_X < l_boundingBox.PosX + l_boundingBox.Width &&
		p_Y > l_boundingBox.PosY && p_Y < l_boundingBox.PosY + l_boundingBox.Height)
	return true;	

	return false;
}

void Button::ExecuteCommand()
{
	if(m_constructorId == 0)
		((m_scene)->*(m_function))(m_sceneState, m_menuFlag);
	if(m_constructorId == 1)
		((m_highscore)->*(m_functionCharChange))(m_buttonId);
	if(m_constructorId == 2)
		((m_highscore)->*(m_functionSave))();
}

void Button::Render()
{
	if(*m_clickable == true)
			m_renderComponentInterface->RenderObject(m_boundingBox, ENEMY1); 
}