#include "Level.h"


Level::Level(void)
{
	m_mapEdges.posX = 0;
	m_mapEdges.posY = 0;
	m_PaddleHasDied = false;
	m_map = NULL;
	m_nrOfEnemies = 0;
}


Level::~Level(void)
{
	delete m_paddle;
	delete m_map;
	delete m_ball;
}

void Level::Init( int p_lvlNr, int p_lvlWidth, int p_lvlHeight )
{
	//m_nrOfEnemies = 5; //Test only
	m_mapEdges.Width = p_lvlWidth; 
	m_mapEdges.Height = p_lvlHeight; 
	string tmpString = "level"+to_string(p_lvlNr);
	m_map = LevelImporter::LoadLevel(tmpString);
	m_paddle = new Paddle(p_lvlWidth/2, p_lvlHeight-50, 20, 5, p_lvlWidth); //example values
	m_ball = new Ball();
	int l_ballHeight = 20; //TEST ONLY
	int l_ballWidth = 20; //TEST ONLY

	m_ball->Init(CalculateBallOnPaddlePosX(), m_paddle->GetPosY()-m_paddle->GetBoundingBox().Height-l_ballHeight, l_ballWidth, l_ballHeight, 10, m_mapEdges); //SPEED?!
	//TODO Create enemies from data in m_map

}

void Level::Update( int p_mousePosX )
{
	m_paddle->Update(p_mousePosX);
	m_ball->Update();
	CheckAllCollisions();
	//TODO Update enemy position, make ball stick to paddle and shoot with mouse button
}

void Level::Render()
{
	m_paddle->Render();
	m_ball->Render();
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
	if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), m_ball->GetBoundingBox()))
		m_ball->BallBounceAgainstPaddle(m_paddle->GetBoundingBox());

	//Paddle vs PowerUp
	//if(BoundingBoxIntersect(m_paddle->GetBoundingBox(), PowerUpBoundingBox))
		//Stuff happens
	
	//Ball vs Enemy
	//if(BoundingBoxIntersect(m_ball->GetBoundingBox(), m_enemy->GetBoundingBox()))
		//m_ball->BallBounceAgainstEnemy(m_enemy->GetBoundingBox());
		//Enemy hit

	//Ball vs Laser
	//if(BoundingBoxIntersect(BallBoundingBox, LaserBoundingBox))
		//Remove laser
}

bool Level::BoundingBoxIntersect(BoundingBox p_box1, BoundingBox p_box2)
{
	if((p_box1.posX+p_box1.Width > p_box2.posX && p_box1.posX < p_box2.posX+p_box2.Width) && 
		p_box1.posY+p_box1.Height > p_box2.posY && p_box1.posY < p_box2.posY+p_box2.Height)
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

int Level::CalculateBallOnPaddlePosX()
{
	return m_paddle->GetPosX()+m_paddle->GetBoundingBox().Width; //byt ut mot b�ttre algoritm!!!
}

/*void Level::SetGraphicalInterface(RenderComponentInterface* p_renderComp)
{
	m_renderComp = p_renderComp;
	m_paddle->SetGraphicalInterface(p_renderComp);
	//Set the interface for enemy,ball
}*/

/* BALL BOUNCE
Enum left, right, top, down, i bollen och block
j�mf�r mittpunkt p� bollen och paddlen
*/