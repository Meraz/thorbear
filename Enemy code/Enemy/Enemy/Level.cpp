#include "Level.h"


Level::Level(void)
{
	m_mapEdges.farTopLeftX = 0;
	m_mapEdges.farTopLeftY = 0;
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
}

void Level::Init( int p_lvlNr, int p_lvlWidth, int p_lvlHeight )
{
	m_mapEdges.width = p_lvlWidth; 
	m_mapEdges.height = p_lvlHeight; 
	//string tmpString = "level"+to_string(p_lvlNr); //Commented away during enemy test
	//m_map = LevelImporter::LoadLevel(tmpString);	//Commented away during enemy test
	m_paddle = new Paddle(p_lvlWidth/2, p_lvlHeight-50, 20, 5, p_lvlWidth); //example values
	//TODO Create enemies from data in m_map

	//TEST ONLY\\
	//-------------------------------------------
	Enemy* temp = new ShootingEnemy(); 
	temp->Init(10,10,10,10); 
	m_enemy.push_back(temp); 
	m_nrOfEnemies = 1;
	m_mapEdges.width = 30;
	//------------------------------------------
}

void Level::Update( int p_mousePosX )
{
	m_paddle->Update(p_mousePosX);
	CheckAllCollisions();
	switch(m_currentEnemyDirection)
	{
	case HORIZONTAL:
		for(int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy.at(i)->Update(m_enemyVelocityX, 0);
			if(m_enemy.at(i)->GetBoundingBox().farTopLeftX <= m_mapEdges.farTopLeftX || 
				m_enemy.at(i)->GetBoundingBox().farTopLeftX + m_enemy.at(i)->GetBoundingBox().width >= m_mapEdges.farTopLeftX + m_mapEdges.width)
			{
				m_enemyVelocityX *= -1;
				m_currentEnemyDirection = VERTICAL;
				m_targetY = m_enemy.at(0)->GetBoundingBox().farTopLeftY + m_enemy.at(0)->GetBoundingBox().height;
				m_currentEnemyY = m_enemy.at(0)->GetBoundingBox().farTopLeftY;
			}
		}
		break;
	case VERTICAL:
		m_currentEnemyY += m_enemyVelocityY;
		if(m_currentEnemyY > m_targetY)
		{
			m_currentEnemyDirection = HORIZONTAL;
			if(m_targetY >= m_paddle->GetBoundingBox().farTopLeftY)
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

	m_enemy.at(0)->WritePosition();
	
	//TODO make ball stick to paddle and shoot with mouse button
}

void Level::Render()
{
	m_paddle->Render();
	//TODO Render enemies, lasers, powerups and ball. 
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
	if((p_box1.farTopLeftX+p_box1.width > p_box2.farTopLeftX && p_box1.farTopLeftX < p_box2.farTopLeftX+p_box2.width) && 
		p_box1.farTopLeftY+p_box1.height > p_box2.farTopLeftY && p_box1.farTopLeftY < p_box2.farTopLeftY+p_box2.height)
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

/*void Level::SetGraphicalInterface(RenderComponentInterface* p_renderComp)
{
	m_renderComp = p_renderComp;
	m_paddle->SetGraphicalInterface(p_renderComp);
	//Set the interface for enemy,ball
}*/

/* BALL BOUNCE
Enum left, right, top, down, i bollen och block
jämför mittpunkt på bollen och paddlen
*/