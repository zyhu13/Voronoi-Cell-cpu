#ifndef _Point_H
#define _Point_H
#include <GL/glut.h>
#include <GL/glu.h>

#include "vector.h"


class Point
{
private:
	double x,y,z;
	double lowest_dist;
	int color_index;

public:
	Point();
	Point(double,double,double,double, int);

	double getPointDistance(){return lowest_dist;}
	double getPointX(){return x;}
	double getPointY(){return y;}
	double getPointZ(){return z;}
	double getColor(){return color_index;}

	void setPointDistance(double d){lowest_dist=d;}
};

Point::Point()
{
	x=0;
	y=0;
	z=0;
	lowest_dist=0;
	color_index=0;
}

Point::Point(double x_value, double y_value, double z_value, double lowest, int color)
{
	x=x_value;
	y=y_value;
	z=z_value;
	lowest_dist=lowest;
	color_index=color;
}

#endif