#include "Particle.h"


Particle::Particle(void)
{
}


Particle::~Particle(void)
{
}

void Particle::Init( Vect3 p_position, Vect3 p_scale, Vect3 p_direction, Vect3 p_acceleration, Vect3 p_color, Vect3 p_endColor, float p_lifeTime, float p_speed, float p_angle )
{
	m_position	   = p_position;
	m_scale		   = p_scale;   
	m_velocity	   = p_direction * p_speed;   
	m_acceleration = p_acceleration; 
	m_color		   = p_color;   
	m_endColor	   = p_endColor;
	m_lifeTime	   = m_startLifeTime = p_lifeTime;
	m_angle		   = p_angle;   
	m_dead		   = false;
	
	m_diffColor	   = m_endColor - m_color; 
}

bool Particle::Update( float p_dt )
{
	if (!m_dead)
	{
		m_color = m_color + (m_diffColor * (p_dt/m_startLifeTime));
		m_lifeTime -= p_dt;
		m_velocity = (m_velocity + m_acceleration);
		m_position = m_position + (m_velocity * p_dt);

		if (m_lifeTime <= 0.0f)
		{
			KillParticle();
			return true;
		}
	}
	return false;
}

Vect3 Particle::GetColor()
{
	return m_color;
}

Vect3 Particle::GetScale()
{
	return m_scale; 
}

Vect3 Particle::GetPosition()
{
	return m_position;
}

void Particle::KillParticle()
{
	m_dead = true;

	m_lifeTime		= 0;
	m_velocity		= Vect3(0.0f);
	m_acceleration	= Vect3(0.0f);
	m_position		= Vect3(-1000.0f, -1000.0f, -1000.0f);
}
