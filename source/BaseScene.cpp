#include "BaseScene.h"


BaseScene::BaseScene()
{
	m_menuFlag = -1;
}

BaseScene::~BaseScene()
{

}

void BaseScene::Initialize(RenderComponentInterface* p_renderComponentInterface)
{
	m_renderComponentInterface = p_renderComponentInterface;
}

SceneState::State BaseScene::GetSceneState()
{
	return m_sceneState;
}

int BaseScene::GetMenuFlag()
{
	return m_menuFlag;
}

void BaseScene::ChangeCurrentState(SceneState::State l_sceneState, int l_menuFlag)
{
	m_sceneState = l_sceneState;
	m_menuFlag = l_menuFlag;
}

void BaseScene::RenderParticleEffect( int p_x, int p_z )
{
	int l_random = rand() % 100;

	ParticleEmitterDesc l_desc;
	l_desc.position			= Vect3(250.0f, 350.0f, 50.0f);
	l_desc.lifeTimeMin		= 0.3f;
	l_desc.lifeTimeMax		= 0.5f;
	l_desc.acceleration		= Vect3(0.0f, -1.0f, 0.0f);
	l_desc.nrOfParticles	= 100;
	l_desc.speedMin			= 50.0f;
	l_desc.speedMax			= 300.0f;
	l_desc.scale			= Vect3(0.7f, 0.7f, 2.5f);
	l_desc.startColor		= Vect3(1.0f, 0.0f, 0.0f);
	l_desc.endColor			= Vect3(1.0f, 1.0f, 0.0f);
	m_renderComponentInterface->CreateParticleEmitter(l_desc);	
}
