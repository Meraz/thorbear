#include "Game.h"


Game::Game()
{
	
}


Game::~Game()
{
}

void Game::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	m_renderComponentInterface = p_renderComponentInterface;
}

void Game::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY /* add keyboard parameters here*/)
{

}


void Game::Render()
{
	BoundingBox a;
	a.PosX = -10;
	a.PosY = 0;
	m_renderComponentInterface->RenderObject(a, ENEMY1);
	BoundingBox b;
	b.PosX = 0;
	b.PosY = 0;
	m_renderComponentInterface->RenderObject(b, ENEMY1);
	BoundingBox c;
	c.PosX = 10;
	c.PosY = 0;
	m_renderComponentInterface->RenderObject(c, ENEMY1);

}


