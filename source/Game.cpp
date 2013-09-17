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

void Game::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY /* add keyboard parameters here*/)
{
	m_renderComponentInterface->Render();
}


void Game::Render()
{

}


