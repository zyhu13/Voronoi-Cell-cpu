#ifndef _IMFUN_H
#define _IMFUN_H

class imfun{
    //A x^2 + B y^2 + C z^2 + D xy + E xz + F yz + G x + H y + I z + J = 0.
	// A x + B y + C z + D = 0.
private:
	double A;
    double B;
    double C;
    double D;
    double E;
    double F;
    double G;
    double H;
    double I;
    double J;
	int type_index;
	
public:
    imfun();
	imfun(double, double, double, double, double, double, double, double, double, double, int);
	imfun(double, double, double, double);

	double getA(){return A;}
    double getB(){return B;}
    double getC(){return C;}
    double getD(){return D;}
    double getE(){return E;}
    double getF(){return F;}
    double getG(){return G;}
    double getH(){return H;}
    double getI(){return I;}
    double getJ(){return J;}
	int getType(){return type_index;}
};

imfun::imfun()
{
	A=1;B=1;C=1;D=1;E=1;F=1;G=1;H=1;I=1;J=1; type_index=1;
}

imfun::imfun(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, int type)
{
	A=a;
    B=b;
    C=c;
    D=d;
    E=e;
    F=f;
    G=g;
    H=h;
    I=i;
    J=j;
	type_index=type;
}

imfun::imfun(double a, double b, double c, double d)
{
	A=a;
    B=b;
    C=c;
    D=d;
	type_index=0;
}


#endif