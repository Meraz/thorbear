#ifndef VECT3_H
#define VECT3_H

struct Vect3
{
	float r, g, b;

	Vect3()
	{
		r = g = b = 0.0f;
	}
	Vect3(float p_color)
	{
		r = g = b = p_color;
	}
	Vect3(float p_r, float p_g, float p_b)
	{
		r = p_r;
		g = p_g;
		b = p_b;
	}
	//Vect3 operator*(Vect3 p_vector)
	//{
	//	return Vect3(r*p_vector.r, g*p_vector.g, b*p_vector.b);
	//}
	Vect3 operator*(float p_scalar)
	{
		return Vect3(r*p_scalar, g*p_scalar, b*p_scalar);
	}
	Vect3 operator+(Vect3 p_vector)
	{
		return Vect3(r+p_vector.r, g+p_vector.g, b+p_vector.b);
	}
	Vect3 operator-(Vect3 p_vector)
	{
		return Vect3(r-p_vector.r, g-p_vector.g, b-p_vector.b);
	}
};
#endif