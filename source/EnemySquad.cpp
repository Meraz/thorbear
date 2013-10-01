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
	CalculateBoundingBox();
	m_currentEnemyY = m_BoundingBox.PosY;
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
	{
		m_laser.at(i)->Update(p_deltaTime);
		if(m_laser.at(i)->GetBoundingBox().PosY + m_laser.at(i)->GetBoundingBox().Height < 0)
			EraseMember(BALL, i); //Change Ball to Laser once this define has been implemented
	}
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
		CalculateBoundingBox();
		if(m_BoundingBox.PosX <= m_mapEdges.PosX || 
			m_BoundingBox.PosX + m_BoundingBox.Width >= m_mapEdges.PosX + m_mapEdges.Width)
		{
			for(unsigned int i = 0; i < m_enemy.size(); i++)
			{
				m_enemy.at(i)->Update(m_velocity * (-p_deltaTime), m_currentEnemyDirection, p_deltaTime);
			}
			m_velocity *= -1;
			m_currentEnemyDirection = VERTICAL;
			m_currentEnemyY = m_BoundingBox.PosY;
			m_targetY = m_currentEnemyY - m_enemy.at(0)->GetBoundingBox().Height;

			break;
		}

		break;
	case VERTICAL:
		m_currentEnemyY -= abs(m_velocity * p_deltaTime);
		if(m_currentEnemyY < m_targetY)
		{
			m_currentEnemyY = m_targetY;
			m_currentEnemyDirection = HORIZONTAL;
			break;
		}
		for(unsigned int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy.at(i)->Update(abs(m_velocity * p_deltaTime), m_currentEnemyDirection, p_deltaTime);
		}
		CalculateBoundingBox();
		break;
	}
}

void EnemySquad::HandleLaserFiring()
{
	vector<int> l_fireIndex = CheckLowestEnemiesInSquad();
	for(unsigned int i = 0; i < l_fireIndex.size(); i++)
	{
		if(m_enemy.at(l_fireIndex.at(i))->WantsToFire())
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

void EnemySquad::CalculateBoundingBox()
{
	float l_x,l_y;
	float l_width, l_height;
	l_x = l_height = 10000;
	l_y = l_width = 0;
	for(unsigned int i = 0; i < m_enemy.size(); i++)
	{
		if(l_x > m_enemy.at(i)->GetBoundingBox().PosX)
			l_x = m_enemy.at(i)->GetBoundingBox().PosX;
		if(l_y < m_enemy.at(i)->GetBoundingBox().PosY)
			l_y = m_enemy.at(i)->GetBoundingBox().PosY;
		if(l_width < m_enemy.at(i)->GetBoundingBox().PosX + m_enemy.at(i)->GetBoundingBox().Width)
			l_width = m_enemy.at(i)->GetBoundingBox().PosX + m_enemy.at(i)->GetBoundingBox().Width;
		if(l_height > m_enemy.at(i)->GetBoundingBox().PosY - m_enemy.at(i)->GetBoundingBox().Height)
			l_height = m_enemy.at(i)->GetBoundingBox().PosY - m_enemy.at(i)->GetBoundingBox().Height;
	}

	m_BoundingBox.PosX = l_x;
	m_BoundingBox.PosY = l_y;
	m_BoundingBox.Width = l_width - l_x;
	m_BoundingBox.Height = l_height + l_y;
}

vector<int> EnemySquad::CheckLowestEnemiesInSquad()
{
	vector<int> l_validToFireIndex;
	int l_currentEnemyIndex;
	for(unsigned int i = 0; i < m_enemy.size(); i++)
	{
		l_currentEnemyIndex = i;
		for(unsigned int j = 0; j < m_enemy.size(); j++)
		{
			if(m_enemy.at(i)->GetBoundingBox().PosX == m_enemy.at(j)->GetBoundingBox().PosX &&
				m_enemy.at(i)->GetBoundingBox().PosY < m_enemy.at(j)->GetBoundingBox().PosY)
				l_currentEnemyIndex = j;
		}
		l_validToFireIndex.push_back(l_currentEnemyIndex);
	}
	std::sort( l_validToFireIndex.begin(), l_validToFireIndex.end() );
	l_validToFireIndex.erase( std::unique(l_validToFireIndex.begin(), l_validToFireIndex.end()), l_validToFireIndex.end());

	return l_validToFireIndex;
}

