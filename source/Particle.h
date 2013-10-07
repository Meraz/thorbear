#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vect3.h"
class Particle
{
public:
	Particle();
	~Particle();
	void Init(	Vect3 p_position,
		Vect3 p_scale,
		Vect3 p_direction,
		Vect3 p_acceleration,
		Vect3 p_color,
		Vect3 p_endColor,
		float p_lifeTime,
		float p_speed,
		float p_angle);
	
	Vect3 GetPosition();
	Vect3 GetScale();
	Vect3 GetColor();

	void KillParticle();
	
	bool Update(float p_dt);
private:
	Vect3 m_position;
	Vect3 m_scale;
	Vect3 m_acceleration;
	Vect3 m_color;
	Vect3 m_diffColor;
	Vect3 m_endColor;
	Vect3 m_velocity;

	float m_lifeTime;
	float m_startLifeTime;
	float m_angle;

	bool m_dead;
};

#endif