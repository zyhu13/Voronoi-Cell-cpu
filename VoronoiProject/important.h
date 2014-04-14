#ifndef _IMPORTANT_H
#define _IMPORTANT_H

#include "sphere.h"
#include "ray.h"
#include "imfun.h"
#include "point.h"
#include <vector>
using namespace std;

#define PI 3.141593
#define INFINITY 100000
vector <imfun> Bisector;
vector <Point> list_Points;
vector <Ray> list_Rays;

void sample() //6*201*201 sampling density
{
               //cube[1] projection surface z=1   
			for (double u=-1; u<1; u+=0.01)
				for(double v=-1; v<1; v+=0.01)
					{
						double normalized_factor=sqrt(u*u+v*v+1);
						double x=u/normalized_factor;
						double y=v/normalized_factor;
						double z=1/normalized_factor;

						Vect ray_dir=Vect(x,y,z);
						Ray ray(Vect(x,y,z),ray_dir);
						list_Rays.push_back(ray);
			      }

				//cube[2] projection surface z=-1 
	        
			for (double u=-1; u<1; u+=0.01)
				for(double v=-1; v<1; v+=0.01)
					{
						double normalized_factor=sqrt(u*u+v*v+1);
						double x=u/normalized_factor;
						double y=v/normalized_factor;
						double z=-1/normalized_factor;

						Vect ray_dir=Vect(x,y,z);
						Ray ray(Vect(x,y,z),ray_dir);
						list_Rays.push_back(ray);
			      }

				//cube[3] x=1
			for (double u=-1; u<1; u+=0.01)
				for(double v=-1; v<1; v+=0.01)
					{
						double normalized_factor=sqrt(u*u+v*v+1);
						double x=1/normalized_factor;
						double y=u/normalized_factor;
						double z=v/normalized_factor;

						Vect ray_dir=Vect(x,y,z);
						Ray ray(Vect(x,y,z),ray_dir);
						list_Rays.push_back(ray);
			      }

			// cube[4] x=-1
			for (double u=-1; u<1; u+=0.01)
				for(double v=-1; v<1; v+=0.01)
					{
						double normalized_factor=sqrt(u*u+v*v+1);
						double x=-1/normalized_factor;
						double y=u/normalized_factor;
						double z=v/normalized_factor;

						Vect ray_dir=Vect(x,y,z);
						Ray ray(Vect(x,y,z),ray_dir);
						list_Rays.push_back(ray);
			      }
			// cube[5]  y=1    
			for (double u=-1; u<1; u+=0.01)
				for(double v=-1; v<1; v+=0.01)
					{
						double normalized_factor=sqrt(u*u+v*v+1);
						double x=u/normalized_factor;
						double y=1/normalized_factor;
						double z=v/normalized_factor;

						Vect ray_dir=Vect(x,y,z);
						Ray ray(Vect(x,y,z),ray_dir);
						list_Rays.push_back(ray);
			      }

				//cube[6]  y=-1
			for (double u=-1; u<1; u+=0.01)
				for(double v=-1; v<1; v+=0.01)
					{
						double normalized_factor=sqrt(u*u+v*v+1);
						double x=u/normalized_factor;
						double y=-1/normalized_factor;
						double z=v/normalized_factor;

						Vect ray_dir=Vect(x,y,z);
						Ray ray(Vect(x,y,z),ray_dir);
						list_Rays.push_back(ray);
			      }

	}

// Cx1, Cy1, Cz1, R1 - sphere center and radius
void ImplicitBisector(Sphere sphere1,  Sphere sphere2)
{
    double Cx1=sphere1.getSphereCenter().getVectX();
	double Cy1=sphere1.getSphereCenter().getVectY();	
	double Cz1=sphere1.getSphereCenter().getVectZ();
	double R1=sphere1.getSphereRadius();	
    
	double Cx2=sphere2.getSphereCenter().getVectX();	
	double Cy2=sphere2.getSphereCenter().getVectY();	
	double Cz2=sphere2.getSphereCenter().getVectZ();	
	double R2=sphere2.getSphereRadius(); 	  	 

	if (R1 == R2 ) //bisector is a plane
	{
		//A*x+B*y+C*z+D=0
		double A=2*(Cx1-Cx2);
		double B=2*(Cy1-Cy2);
		double C=2*(Cz1-Cz2);
		double D=-(Cx1*Cx1-Cx2*Cx2+Cy1*Cy1-Cy2*Cy2+Cz1*Cz1-Cz2*Cz2);
		imfun fun(A,B,C,D);
		//printf("%f X+ %f Y +%f Z + %f = 0 \n", A,B,C,D);
		Bisector.push_back(fun);
	}

	else 
	{    // resulting implicit quadric surface:
         //A x^2 + B y^2 + C z^2 + D xy + E xz + F yz + G x + H y + I z + J = 0.
		//The bisector is porabola and the equation is:
		//sqrt[(X-Cx1)^2 + (Y-Cy1)^2 + (Z-Cz1)^2] - sqrt[(X-Cx2)^2 + (Y-Cy2)^2 + (Z-Cz2)^2] = (R1 - R2)
    
		// Let:
		// R = R1-R2
		// K = (Cx2^2-Cx1^2) + (Cy2^2-Cy1^2) + (Cz2^2-Cz1^2) - R^2
		// Dx = Cx1-Cx2; Dy = Cy1-Cy2; Dz = Cz1-Cz2;
    
		// Expanding the formula gives us:
		// [4R^2 - 4Dx^2]X^2 + [4R^2 - 4Dy^2]Y^2 + [4R^2 - 4Dz^2]Z^2
		//    +[-8DxDy]XY  +     [-8DxDz]XZ  +     [-8DyDz]YZ
		// + [-8R^2Cx1 - 4KDx]X
		// + [-8R^2Cy1 - 4KDy]Y
		// + [-8R^2Cz1 - 4KDz]Z
		// + [4R^2(Cx1^2 + Cy1^2 + Cz1^2) - K^2]
		// = 0
    
		double R = R1-R2;
		double K = (Cx2*Cx2-Cx1*Cx1) + (Cy2*Cy2-Cy1*Cy1) + (Cz2*Cz2-Cz1*Cz1) - R*R;
		double Dx = Cx1-Cx2, Dy = Cy1-Cy2, Dz = Cz1-Cz2;
    
		double A = (4*R*R - 4*Dx*Dx); //X^2 coefficient
		double B = (4*R*R - 4*Dy*Dy); //Y^2 coefficient
		double C = (4*R*R - 4*Dz*Dz); //Z^2 coefficient
    
		double D = (-8*Dx*Dy); //XY coefficients
		double E = (-8*Dx*Dz); //XZ coefficients
		double F = (-8*Dy*Dz); //YZ coefficients
    
		double G = (-8*R*R*Cx1 - 4*K*Dx); //X coefficient
		double H = (-8*R*R*Cy1 - 4*K*Dy); //Y coefficient
		double I = (-8*R*R*Cz1 - 4*K*Dz); //Z coefficient
    
		double J = (4*R*R*(Cx1*Cx1 + Cy1*Cy1 + Cz1*Cz1) - K*K);//constant coefficient
		
		int type;
		if (R1<R2) type=1; // the sphere is bigger than base sphere
		if (R1>R2) type=2; // the sphere is smaller than base sphere
		imfun fun(A,B,C,D,E,F,G,H,I,J, type);
		//printf("%f x^2 + %f y^2 + %f z^2 + %f xy + %f xz + %f yz + %f x + %f y + %f z + %f = 0\n", A,B,C,D,E,F,G,H,I,J);
		Bisector.push_back(fun);
	}
}

double findIntersection(Ray ray, imfun fun)
{
    Vect ray_direction=ray.getRayDirection();
    double x=ray_direction.getVectX();
    double y=ray_direction.getVectY();
    double z=ray_direction.getVectZ();
   
	if (fun.getType()==0) //bisector is a plane
	{
		//plug the ray into the bisector implicit function
		//b*t+c=0  linear equation
		 double A=fun.getA();
         double B=fun.getB();
         double C=fun.getC();
         double D=fun.getD();

	     double b=A*x+B*y+C*z;
		 double c=A*x+B*y+C*z+D;
		 
		 if (b!=0) 
		 {
			 if (-c/b > 0) return -c/b;
		        else return INFINITY;
		 }
		 
		 else { printf("Error"); return INFINITY;}
	}

	else // bisector is a parabola
	{ 
		double A=fun.getA();
		double B=fun.getB();
		double C=fun.getC();
		double D=fun.getD();
		double E=fun.getE();
		double F=fun.getF();
		double G=fun.getG();
		double H=fun.getH();
		double I=fun.getI();
		double J=fun.getJ();

		// quadratic equation in parametric of (t). a*t^2+b*t+c=0
		double a=(A*x*x+B*y*y+C*z*z+D*x*y+E*x*z+F*y*z);
		double b=(A*2*x*x+B*2*y*y+C*2*z*z+D*2*x*y+E*2*x*z+F*2*y*z+G*x+H*y+I*z);
		double c=J+A*x*x+B*y*y+C*z*z+D*x*y+E*x*z+F*y*z+G*x+H*y+I*z;
        
		double discriminant=b*b-4*c*a;
		//printf("%f\n", discriminant);

		if (discriminant>0)//the ray intersects wiht the bisector
		{
			double root_1=(-b-sqrt(discriminant))/(2*a); //the first root
		    double root_2=(-b+sqrt(discriminant))/(2*a); //the second root
			
			if(fun.getType()==1)  // the sphere is bigger than base sphere
				{ 
					if(root_2 > 0) return root_2;
			           else return INFINITY;
		         }

			else // fun.getType()==2)-- the sphere is smaller than base sphere	
			     {
					 if(root_1 > 0) return root_1;
					 else return INFINITY;
			      }
		}
       else return INFINITY; // the ray missed the bisecotr 
   }
}

void lowerEnvelope(Ray ray)  
{
	double min=findIntersection(ray, Bisector[0]);
	int min_index=0;

	for(int i=1; i<Bisector.size(); i++)
	{
		double root=findIntersection(ray, Bisector.at(i));
		//if (root==-1) 
			//continue;
		
		if (root<min) { 
			min_index=i;
			min=root;
		}
	}
		//printf("This ray with %d%d%d direction intersects with no bisectors", ray.getRayDirection().getVectX(),ray.getRayDirection().getVectY(),ray.getRayDirection().getVectZ());
	if (min==INFINITY) 
		{
			Point newpoint(INFINITY,INFINITY,INFINITY,INFINITY,0) ;
		    list_Points.push_back(newpoint);
	}
	else
	{    
	    double lowest_dist=min;
		double x=ray.getRayOrigin().getVectX()+ray.getRayDirection().vectMult(lowest_dist).getVectX();
		double y=ray.getRayOrigin().getVectY()+ray.getRayDirection().vectMult(lowest_dist).getVectY();
		double z=ray.getRayOrigin().getVectZ()+ray.getRayDirection().vectMult(lowest_dist).getVectZ();
		Point newpoint(x,y,z,lowest_dist, min_index) ;
		list_Points.push_back(newpoint); // correspondence between list_ray vs list_point
	    }
}

#endif 