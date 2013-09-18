#include "Game.h"


Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	m_renderComponentInterface = p_renderComponentInterface;

}

void Game::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY /* add keyboard parameters here*/)
{
	BoundingBox a;
	a.farTopLeftX = 0;
	a.farTopLeftY = 0;
	a.farTopLeftZ = 0;
	a.heigth = 50;
	a.width = 50;
	a.depth = 50;
	m_renderComponentInterface->RenderObject(a, ENEMY1);

	m_renderComponentInterface->Render();
}


void Game::Render()
{

}


