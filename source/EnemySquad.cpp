#include "EnemySquad.h"
#include <cmath>
//DEBUGGING ONLY
/*#include <windows.h>
#include <sstream>
#include <iostream>*/
EnemySquad::EnemySquad()
{
	m_velocity = 0;
	m_BoundingBox = BoundingBox(0,0,0,0);
}

EnemySquad::~EnemySquad()
{
	vector<Enemy*>().swap(m_enemy);
	vector<Laser*>().swap(m_laser);
}

void EnemySquad::Init(BoundingBox p_mapEdges, float p_velocity, vector<Enemy*> p_enemy)
{
	m_mapEdges = p_mapEdges;
	m_velocity = p_velocity;
	m_enemy = p_enemy;
	m_currentEnemyDirection = HORIZONTAL;
	m_currentEnemyY = FindLowestEnemyRow();
}

void EnemySquad::Update( float p_deltaTime )
{
	MoveEnemies(p_deltaTime);
	HandleLaserFiring();

	//DEBUGGING ONLY
	/*std:wstringstream ss;
	ss << "Crazy Enemy: " << m_enemy.at(9)->GetBoundingBox().PosX << "Normal Enemy: " << m_enemy.at(0)->GetBoundingBox().PosX << "\n";
	std::wstring tt = ss.str();
	OutputDebugStringW(tt.c_str());*/

	for(unsigned int i = 0; i < m_laser.size(); i++)
		m_laser.at(i)->Update(p_deltaTime);
}

void EnemySquad::MoveEnemies( float p_deltaTime)
{
	switch(m_currentEnemyDirection)
	{
	case HORIZONTAL:
		for(unsigned int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy.at(i)->Update(m_velocity * p_deltaTime, m_currentEnemyDirection, p_deltaTime);
		}
		for(unsigned int i = 0; i < m_enemy.size(); i++)
			if(m_enemy.at(i)->GetBoundingBox().PosX <= m_mapEdges.PosX || 
				m_enemy.at(i)->GetBoundingBox().PosX + m_enemy.at(i)->GetBoundingBox().Width >= m_mapEdges.PosX + m_mapEdges.Width)
			{
				m_velocity *= -1;
				m_currentEnemyDirection = VERTICAL;
				m_currentEnemyY = FindLowestEnemyRow(); //Use the lowest row so that we can use the same variable for laser firing checks
				m_targetY = m_currentEnemyY - m_enemy.at(0)->GetBoundingBox().Height;

				for(unsigned int i = 0; i < m_enemy.size(); i++)
				{
					m_enemy.at(i)->Update(m_velocity * (-p_deltaTime), m_currentEnemyDirection, p_deltaTime);
				}

				break;
			}
		break;
	case VERTICAL:
		m_currentEnemyY -= abs(m_velocity * p_deltaTime);
		if(m_currentEnemyY < m_targetY)
		{
			m_currentEnemyY = m_targetY; //Helps for checking which enemies will fire lasers
			m_currentEnemyDirection = HORIZONTAL;
			break;
		}
		for(unsigned int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy.at(i)->Update(abs(m_velocity * p_deltaTime), m_currentEnemyDirection, p_deltaTime);

		}
		break;
	}
}

float EnemySquad::FindLowestEnemyRow()
{
	float l_lowestRow = 1000;
	for(unsigned int i = 0; i < m_enemy.size(); i++)
	{
		if(m_enemy.at(i)->GetBoundingBox().PosY < l_lowestRow) //The lower the Y value, the lower the row 
			l_lowestRow = m_enemy.at(i)->GetBoundingBox().PosY;
	}

	return l_lowestRow;
}

void EnemySquad::HandleLaserFiring()
{
	for(unsigned int i = 0; i < m_enemy.size(); i++)
	{
		if(m_enemy.at(i)->WantsToFire())
			if(m_enemy.at(i)->GetBoundingBox().PosY - (m_enemy.at(i)->GetBoundingBox().Height / 2) <= m_currentEnemyY) //Make sure that only the enemies in the lowest row gets to fire
			{
				Laser* temp = new Laser();
				BoundingBox box(m_enemy.at(i)->GetBoundingBox().PosX, m_enemy.at(i)->GetBoundingBox().PosY);
				box.Height = 10;
				box.Width = 1;
				temp->Init(m_renderComp, 200, box); //TODO Don't hard code velocity in the end
				m_laser.push_back(temp);
			}
	}
}

void EnemySquad::Render()
{
	for(unsigned int i = 0; i < m_enemy.size(); i++)
		m_enemy.at(i)->Render();

	for(unsigned int i = 0; i < m_laser.size(); i++)
		m_laser.at(i)->Render();
}

void EnemySquad::SetSquadRenderComponent( RenderComponentInterface* p_renderComp )
{
	m_renderComp = p_renderComp;
	for(unsigned int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy.at(i)->SetRenderComponentInterface(p_renderComp);
	}
}

BoundingBox EnemySquad::GetBoundingBox()
{
	return m_BoundingBox;
}

int EnemySquad::GetNumOfEnemies()
{
	return m_enemy.size();
}

vector<Enemy*> EnemySquad::GetEnemies()
{
	return m_enemy;
}

vector<Laser*> EnemySquad::GetLasers()
{
	return m_laser;
}

void EnemySquad::EraseMember( int p_type, int p_vectorPos )
{
	if(p_type == BALL) //TODO Change to LASER once this define is implemented
		m_laser.erase(m_laser.begin() + p_vectorPos);
	else if(p_type == ENEMY1) //only use ENEMY1 for both types
		m_enemy.erase(m_enemy.begin() + p_vectorPos);
}

