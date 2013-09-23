#include "Level.h"


Level::Level(void)
{
	m_mapEdges.PosX = 0;
	m_mapEdges.PosY = 0;
	m_PaddleHasDied = false;
	m_map = NULL;
	m_nrOfEnemies = 0;
	m_enemyVelocityX = 1;
	m_enemyVelocityY = 1;
	m_currentEnemyDirection = HORIZONTAL;
	m_targetY = 0;
	m_currentEnemyY = 0;
}


Level::~Level(void)
{
	delete m_paddle;
	delete m_map;
	vector<Enemy*>().swap(m_enemy);
}

void Level::Init( int p_lvlNr, int p_lvlWidth, int p_lvlHeight, RenderComponentInterface* p_renderComp )
{

	m_mapEdges.Width = p_lvlWidth; 
	m_mapEdges.Height = p_lvlHeight; 
	string tmpString = "level"+to_string(p_lvlNr); 
	m_map = LevelImporter::LoadLevel(tmpString);	
	m_paddle = new Paddle(p_lvlWidth/2, p_lvlHeight-50, 20, 5, p_lvlWidth); //example values
	m_paddle->Initialize(p_renderComp);
	
	CreateEnemies();

	m_renderComp = p_renderComp;

	for(int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy.at(i)->SetRenderComponentInterface(p_renderComp);
	}
}

void Level::CreateEnemies()
{
	Enemy* temp;
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			if(m_map[i][j] == ENEMY1)
			{
				temp = new ShootingEnemy();
				temp->Init(j * 10, i * 10, 10, 10);
				m_enemy.push_back(temp);
			}
			else if(m_map[i][j] == ENEMY2)
			{
				temp = new DefensiveEnemy();
				temp->Init(j * 10, i * 10, 10, 10);
				m_enemy.push_back(temp);
			}
			m_nrOfEnemies ++;
		}
	}
}

void Level::Update( int p_mousePosX, bool p_isMouseClicked )
{
	m_paddle->Update(p_mousePosX);
	CheckAllCollisions();
	switch(m_currentEnemyDirection)
	{
	case HORIZONTAL:
		for(int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy.at(i)->Update(m_enemyVelocityX, 0);
			if(m_enemy.at(i)->GetBoundingBox().PosX <= m_mapEdges.PosX || 
				m_enemy.at(i)->GetBoundingBox().PosX + m_enemy.at(i)->GetBoundingBox().Width >= m_mapEdges.PosX + m_mapEdges.Width)
			{
				m_enemyVelocityX *= -1;
				m_currentEnemyDirection = VERTICAL;
				m_targetY = m_enemy.at(0)->GetBoundingBox().PosY + m_enemy.at(0)->GetBoundingBox().Height;
				m_currentEnemyY = m_enemy.at(0)->GetBoundingBox().PosY;
			}
		}
		break;
	case VERTICAL:
		m_currentEnemyY += m_enemyVelocityY;
		if(m_currentEnemyY > m_targetY)
		{
			m_currentEnemyDirection = HORIZONTAL;
			if(m_targetY >= m_paddle->GetBoundingBox().PosY)
			{
				//Game Over
			}
		}
		for(int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy.at(i)->Update(0, m_enemyVelocityY);
			
		}
		break;
	}
	
	//TODO make ball stick to paddle and shoot with mouse button
}

void Level::Render()
{
	m_paddle->Render();
	for(int i = 0; i < m_enemy.size(); i++)
		m_enemy.at(i)->Render();
	//TODO lasers, powerups and ball. 
	//m_renderComp->RenderObject(m_bBox, OUTERBOUNDS) Render maps outer bounds/edges
}

void Level::CheckAllCollisions()
{
	
	/*
	BoundingBox LaserBoundingBox;
	LaserBoundingBox.Height = 50;
	LaserBoundingBox.Width	= 20;
	LaserBoundingBox.posX = 400;
	LaserBoundingBox.posY = 740;
	*/
	//Paddle vs Laser
	//if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), LaserBoundingBox))
		//m_PaddleHasDied = true;
	
	//Paddle vs Ball
	//if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), BallBoundingBox))
		//Bounce ball

	//Paddle vs PowerUp
	//if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), PowerUpBoundingBox))
		//Stuff happens
	
	/*for(int i = 0; i < m_enemy.size(); i++)
	{
		//Ball vs Enemy
		//if(BoundingBoxIntersect(BallBoundingBox, EnemyBoundingBox))
			//Ball bounce
			m_enemy.at(i)->TakeDamage();
			if(m_enemy.at(i)->GetNumOfLives() == 0)
				m_enemy.erase(m_enemy.begin() + i);
	}*/

	//Ball vs Laser
	//if(BoundingBoxIntersect(BallBoundingBox, LaserBoundingBox))
		//Remove laser
}

bool Level::BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2)
{
	if((p_box1.PosX+p_box1.Width > p_box2.PosX && p_box1.PosX < p_box2.PosX+p_box2.Width) && 
		p_box1.PosY+p_box1.Height > p_box2.PosY && p_box1.PosY < p_box2.PosY+p_box2.Height)
		return true;
	else
		return false;
}

bool Level::HasPaddleDied()
{
	bool temp = m_PaddleHasDied;
	m_PaddleHasDied = false;

	return temp;
}

int Level::GetNrOfEnemies()
{
	//m_nrOfEnemies--; //For test purposes only
	return m_nrOfEnemies;
}


/* BALL BOUNCE
Enum left, right, top, down, i bollen och block
jämför mittpunkt på bollen och paddlen
*/