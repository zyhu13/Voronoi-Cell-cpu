#ifndef _RAY_H
#define _RAY_H

#include "vector.h"

class Ray
{
private:
	Vect ori,dir;
	//double lowest_dist;

public:
	Ray();
	Ray(Vect, Vect);
	Vect getRayOrigin(){return ori;}
	Vect getRayDirection(){return dir;}
	//double getRayDistance(){return lowest_dist;}

	void setRayOrigin(Vect o){ori=o;}
	void setRayDirection(Vect v){dir=v;}
	//void setRayDistance(double d){lowest_dist=d;}
};

Ray::Ray()
{
	ori=Vect(0,0,0);
	dir=Vect(1,0,0);
	//lowest_dist=0;
}

Ray::Ray(Vect o, Vect d)
{
	ori=o;
	dir=d;
	//lowest_dist=dist;
}

#endif