#ifndef _RENDER_H
#define _RENDER_H

#include <GL/glut.h>
#include <GL/glu.h>

#include "sphere.h"
#include "important.h"
#include <vector>
using namespace std;

void render()
{
	Sphere sphere0(Vect(0,0,0),1); //base sphere is centered at origin with radius=1, unit sphere
	glColor3f(1.0f,0.0f,1.0f); //blue base sphere
	glutSolidSphere(1,50,50); //  use glutSolidSphere to draw the base sphere
	sample();  //sample rays on the base object sphere0

	vector<Sphere> list_Spheres;  //a list to keep track of all the other input spheres
	Sphere sphere1(Vect(0,-5,0),3); 
	list_Spheres.push_back(sphere1);
	Sphere sphere2(Vect(0,5,0),3);
	list_Spheres.push_back(sphere2);
    Sphere sphere3(Vect(-5,0,0),3); 
	list_Spheres.push_back(sphere3);
	Sphere sphere4(Vect(5,0,0),3);
	list_Spheres.push_back(sphere4);
	
	/*Sphere sphere5(Vect(3,4,0),3);
	list_Spheres.push_back(sphere5);
	Sphere sphere6(Vect(-3,4,0),3);
	list_Spheres.push_back(sphere6);
	Sphere sphere7(Vect(-3,-4,0),3);
	list_Spheres.push_back(sphere7);
	Sphere sphere8(Vect(3,-4,0),3);
	list_Spheres.push_back(sphere8);
	

	glPushMatrix(); 
	glTranslatef(3,4,0); // translate the second sphere onto the ball position
	glColor3f(0.0f,0.0f,1.0f); 
	glutSolidSphere(3,50,50); 
	
	glPopMatrix();
	glPushMatrix(); 
	glTranslatef(-3,4,0); // translate the second sphere onto the ball position
	glColor3f(0.0f,0.0f,1.0f); 
	glutSolidSphere(3,50,50); 
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(-3,-4,0); // translate the second sphere onto the ball position
	glColor3f(0.0f,0.0f,1.0f); 
	glutSolidSphere(3,50,50); 
	glPopMatrix();

	glPushMatrix(); 
	glTranslatef(3,-4,0); // translate the second sphere onto the ball position
	glColor3f(0.0f,0.0f,1.0f); 
	glutSolidSphere(3,50,50); 
	glPopMatrix();
	*/
    glPushMatrix(); 
	glTranslatef(0,-5,0); // translate the first sphere onto the ball position
	glColor3f(1.0f,0.0f,0.0f); 
	glutSolidSphere(3,50,50); 
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(0,5,0); // translate the second sphere onto the ball position
	glColor3f(0.0f,1.0f,0.0f); 
	glutSolidSphere(3,50,50); 
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(-5,0,0); // translate the second sphere onto the ball position
	glColor3f(0.0f,0.0f,1.0f); 
	glutSolidSphere(3,50,50); 
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(5,0,0); // translate the second sphere onto the ball position
	glColor3f(1.0f,1.0f,1.0f); 
	glutSolidSphere(3,50,50); 
	glPopMatrix();

	for(int i=0; i<list_Spheres.size(); i++)
		  ImplicitBisector(sphere0, list_Spheres.at(i)); // calculate all the bisectors

	for(int i=0; i<list_Rays.size(); i++)   //calculate the intersection between the ray and each bisector
		 {
			 lowerEnvelope(list_Rays.at(i));
		 }


	/*for (unsigned u=0; u<list_Points.size(); u++)
		{
			printf("%f\n",list_Points.at(u).getPointDistance());
	    }
		*/
    
	//printf("total number of points is %d\n", list_Points.size());
	//printf("total number of sampled rays is %d\n", list_Rays.size());


	int num_good_point=0;
	int num_bad_point=0;
	

     for (int n=1; n<=6; n++)
		for (int i=0; i<200-1; i++)
		  {
			  for (int j=0; j<200-1; j++)
			  {
					  int pre_index=(n-1)*200*200;
					  if (list_Points.at(pre_index+200*i+j).getPointDistance()==INFINITY )//|| list_Points.at(pre_index+200*i+j+1).getPointDistance()==INFINITY ||list_Points.at(pre_index+200*(i+1)+j).getPointDistance()==INFINITY || list_Points.at(pre_index+200*(i+1)+j+1).getPointDistance()==INFINITY) 
						  {
							  num_bad_point++; 
							  continue;
						   }
					  else
					  {
						  num_good_point++;
				          glPointSize(3.0);
						  //glBegin(GL_POINTS);
						  glBegin(GL_QUADS);
						  int color=list_Points.at(pre_index+200*i+j).getColor();
						  if(color==0)
							   glColor3f(1.0, 0.0, 0.0);
						  else if (color==1)  glColor3f(0.0,1.0,0.0);
						  else if (color==2)  glColor3f(0.0,0.0,1.0);
						  else glColor3f(1.0,1.0,1.0);
						  glVertex3f(list_Points.at(pre_index+200*i+j).getPointX(), list_Points.at(pre_index+200*i+j).getPointY(), list_Points.at(pre_index+200*i+j).getPointZ());
						  glVertex3f(list_Points.at(pre_index+200*(i+1)+j).getPointX(), list_Points.at(pre_index+200*(i+1)+j).getPointY(), list_Points.at(pre_index+200*(i+1)+j).getPointZ());
						  glVertex3f(list_Points.at(pre_index+200*(i+1)+j+1).getPointX(), list_Points.at(pre_index+200*(i+1)+(j+1)).getPointY(), list_Points.at(pre_index+200*(i+1)+j+1).getPointZ()); 
						  glVertex3f(list_Points.at(pre_index+200*i+j+1).getPointX(), list_Points.at(pre_index+200*i+j+1).getPointY(), list_Points.at(pre_index+200*i+j+1).getPointZ());
						  glEnd();
					  }
				}
				  
			}
	

	//printf("number of bad points is %d\n", num_bad_point );
	//printf("number of good points is %d\n", num_good_point );

	
	}


#endif