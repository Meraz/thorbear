#include "Game.h"


Game::Game()
{
	
}


Game::~Game()
{
	delete a;
}

void Game::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	m_renderComponentInterface = p_renderComponentInterface;
	a = new Game();
}

void Game::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY /* add keyboard parameters here*/)
{

}


void Game::Render()
{
	BoundingBox a;
	a.farTopLeftX = -10;
	a.farTopLeftY = 0;
	m_renderComponentInterface->RenderObject(a, ENEMY1);
	BoundingBox b;
	b.farTopLeftX = 0;
	b.farTopLeftY = 0;
	m_renderComponentInterface->RenderObject(b, ENEMY1);
	BoundingBox c;
	c.farTopLeftX = 10;
	c.farTopLeftY = 0;
	m_renderComponentInterface->RenderObject(c, ENEMY1);

}


