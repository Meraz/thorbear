#include "Level.h"


Level::Level(void)
{
	m_mapEdges.PosX = 0;
	m_mapEdges.PosY = 0;
	m_PaddleHasDied = false;
	m_map = NULL;
	m_nrOfEnemies = 0;
	m_enemyVelocityX = 10;
	m_enemyVelocityY = 10;
	m_currentEnemyDirection = HORIZONTAL;
	m_targetY = 0;
	m_currentEnemyY = 0;

	m_mapBorderThickness = 10;
}


Level::~Level(void)
{
	delete m_paddle;
	delete m_map;
	vector<Enemy*>().swap(m_enemy);
}

void Level::Init( int p_lvlNr, int p_lvlWidth, int p_lvlHeight, RenderComponentInterface* p_renderComp )
{
	m_renderComp = p_renderComp;
	m_mapEdges.Width = p_lvlWidth; 
	m_mapEdges.Height = p_lvlHeight; 
	string tmpString = "level"+to_string(p_lvlNr); 
	m_map = LevelImporter::LoadLevel(tmpString);	
	m_paddle = new Paddle(p_lvlWidth/2.0f, 50.0f, 50, 50, p_lvlWidth); //example values
	m_paddle->Initialize(p_renderComp);

	m_ball = new Ball();
	int l_ballHeight = 5; //TEST ONLY
	int l_ballWidth = 5; //TEST ONLY
	m_ball->Init(CalculateBallOnPaddlePosX(), (float)m_paddle->GetPosY()-m_paddle->GetBoundingBox().Height-l_ballHeight, l_ballWidth, l_ballHeight, 200.0f, m_mapEdges, m_renderComp); //SPEED?!

	CreateEnemies();

	for(unsigned int i = 0; i < m_enemy.size(); i++)
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
				temp->Init(j * 20.0f, m_mapEdges.Height - (i * 20.0f), 20, 20, 10.0f);
				m_enemy.push_back(temp);
			}
			else if(m_map[i][j] == ENEMY2)
			{
				temp = new DefensiveEnemy();
				temp->Init(j * 20.0f, m_mapEdges.Height - (i * 20.0f), 20, 20, 10.0f);
				m_enemy.push_back(temp);
			}
			m_nrOfEnemies ++;
		}
	}
}

void Level::Update( int p_mousePosX, bool p_isMouseClicked, float p_deltaTime )
{
	if(m_ball->IsBallDead())
	{
		m_ball->SetPosX(CalculateBallOnPaddlePosX());
		m_ball->SetPosY((float)(m_paddle->GetPosY() + m_paddle->GetBoundingBox().Height));
		if(p_isMouseClicked)
			ShootBallFromPaddle();
	}
	m_paddle->Update(p_mousePosX);
	m_ball->Update(p_deltaTime);
	CheckAllCollisions();
	
	MoveEnemies(p_deltaTime);
}

void Level::MoveEnemies( float p_deltaTime)
{
	switch(m_currentEnemyDirection)
	{
	case HORIZONTAL:
		for(unsigned int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy.at(i)->Update(p_deltaTime, m_currentEnemyDirection);
			if(m_enemy.at(i)->GetBoundingBox().PosX <= m_mapEdges.PosX || 
				m_enemy.at(i)->GetBoundingBox().PosX + m_enemy.at(i)->GetBoundingBox().Width >= m_mapEdges.PosX + m_mapEdges.Width)
			{
				m_enemy.at(0)->SetVelocity(m_enemy.at(0)->GetVelocity()*-1);
				m_currentEnemyDirection = VERTICAL;
				m_targetY = m_enemy.at(0)->GetBoundingBox().PosY - m_enemy.at(0)->GetBoundingBox().Height;
				m_currentEnemyY = FindLowestEnemyRow(); //Use the lowest row so that we can use the same variable for laser firing checks
			}
		}
		break;
	case VERTICAL:
		m_currentEnemyY -= m_enemy.at(0)->GetVelocity() * p_deltaTime;
		if(m_currentEnemyY < m_targetY)
		{
			m_currentEnemyY = m_targetY; //Helps for checking which enemies will fire lasers
			m_currentEnemyDirection = HORIZONTAL;
			if(m_targetY <= m_paddle->GetBoundingBox().PosY)
			{
				//Game Over
			}
		}
		for(unsigned int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy.at(i)->Update(p_deltaTime, m_currentEnemyDirection);

		}
		for(unsigned int i = 0; i < m_laser.size(); i++)
			m_laser.at(i)->Update();
		break;
	}
}

float Level::FindLowestEnemyRow()
{
	float l_lowestRow = 0;
	for(unsigned int i = 0; i < m_enemy.size(); i++)
	{
		if(m_enemy.at(i)->GetBoundingBox().PosY < l_lowestRow) //The higher the Y value, the lower the row 
			l_lowestRow = m_enemy.at(i)->GetBoundingBox().PosY;
	}

	return l_lowestRow;
}

void Level::HandleLaserFiring()
{
	for(unsigned int i = 0; i < m_enemy.size(); i++)
	{
		if(m_enemy.at(i)->WantsToFire())
			if(m_enemy.at(i)->GetBoundingBox().PosY == m_currentEnemyY) //Make sure that only the enemies in the lowest row gets to fire
			{
				Laser* temp = new Laser();
				BoundingBox box(m_enemy.at(i)->GetBoundingBox().PosX, m_enemy.at(i)->GetBoundingBox().PosY);
				box.Height = 5;
				box.Width = 1;
				temp->Init(m_renderComp, 1, box);
			}
	}
}

void Level::Render()
{
	RenderMapEdges();
	m_paddle->Render();
	m_ball->Render();
	for(unsigned int i = 0; i < m_enemy.size(); i++)
		m_enemy.at(i)->Render();

	for(unsigned int i = 0; i < m_laser.size(); i++)
		m_laser.at(i)->Render();
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
	if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), m_ball->GetBoundingBox()))
		m_ball->BallBounceAgainstPaddle(m_paddle->GetBoundingBox());

	//Paddle vs PowerUp
	//if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), PowerUpBoundingBox))
		//Stuff happens
	
	for(unsigned int i = 0; i < m_enemy.size(); i++)
	{
		//Ball vs Enemy
		if(BoundingBoxIntersect(m_ball->GetBoundingBox(), m_enemy.at(i)->GetBoundingBox()))
		{
			m_ball->BallBounceAgainstEnemy(m_enemy.at(i)->GetBoundingBox());
			m_enemy.at(i)->TakeDamage();
			if(m_enemy.at(i)->GetNumOfLives() == 0)
				m_enemy.erase(m_enemy.begin() + i);
		}
	}

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

float Level::CalculateBallOnPaddlePosX()
{
	
	return ((m_paddle->GetPosX()/(m_mapEdges.Width-m_paddle->GetBoundingBox().Width)) * (m_mapEdges.Width - (2 * m_paddle->GetBoundingBox().Width))) + m_paddle->GetBoundingBox().Width - (m_ball->GetBoundingBox().Width/2.0f);
}

void Level::ShootBallFromPaddle()
{
	
	float l_diff = m_ball->GetPosX()+(m_ball->GetBoundingBox().Width/2) - m_paddle->GetPosX()+(m_paddle->GetBoundingBox().Width/2); //length between middle of ball and middle of paddle

	if(l_diff == 0) //if ball is in the middle of paddle
	{
		m_ball->SetDirection((float)cos(0));
	}
	else //set angle to a value between 45 and 135 (degrees)
	{
		m_ball->SetDirection((float)cos((l_diff / ((m_ball->GetBoundingBox().Width/2) + (m_paddle->GetBoundingBox().Width/2))) * 0.7));
	}
	m_ball->ShootBall();
}

void Level::RenderMapEdges()
{
	BoundingBox l_leftSide = BoundingBox(m_mapEdges.PosX - m_mapBorderThickness, m_mapEdges.PosY, m_mapBorderThickness, m_mapEdges.Height + m_mapBorderThickness);
	BoundingBox l_rightSide = BoundingBox(m_mapEdges.PosX + m_mapEdges.Width, m_mapEdges.PosY, m_mapBorderThickness, m_mapEdges.Height + m_mapBorderThickness);
	BoundingBox l_topSide = BoundingBox(m_mapEdges.PosX + m_mapBorderThickness/2, m_mapEdges.PosY + m_mapEdges.Height, m_mapEdges.Width + m_mapBorderThickness, m_mapBorderThickness);

	m_renderComp->RenderObject(l_leftSide, BALL);
	m_renderComp->RenderObject(l_rightSide, BALL);
	m_renderComp->RenderObject(l_topSide, BALL);
}
