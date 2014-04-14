#ifndef _SPHERE_H
#define _SPHERE_H

#include <cmath>
#include "vector.h"

 class Sphere
{
	Vect center;
	double radius;

public:
	Sphere();
	Sphere(Vect, double);

	//method functions
	Vect getSphereCenter(){return center;}
	double getSphereRadius(){return radius;}

	/*virtual Vect getNormalAt(Vect point)
	{
		//normal always points away from the center of a sphere
		Vect normal_Vect=point.vectAdd(center.negative()).normalize();
		return normal_Vect;
	}
	*/

 };

Sphere::Sphere()
{
	center=Vect(0,0,0);
	radius=1.0;
}

Sphere::Sphere(Vect centerValue, double radiusValue)
{
	center=centerValue;
	radius=radiusValue;
}


#endif