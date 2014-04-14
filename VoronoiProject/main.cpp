#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>
#include <string.h>
#include <limits>

#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "imfun.h"
#include "important.h"
#include "render.h"

using namespace std;

//****************************************************
// Basic classes and Global Variables
//****************************************************

class Viewport;

class Viewport {
  public:
    int w, h; // width and height
};

Viewport viewport;

bool wireframe_only = true;
bool smooth_shading = false; 
bool hidden_line = false;

static float scale=1.0f;
static float zoom=0.1f;
static float rotx=0.0f, roty=0.0f;
static float tx=0.0f, ty=0.0f;


//****************************************************
// Simple init function
//****************************************************
void initScene(){
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS); 
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent
}

/* ************************************************************************* */
/* Initialize Light Sources
/* ************************************************************************* */
void initLights() {

	// define and enable light. 
	GLfloat global_ambient[] = { .1f, .1f, .1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	GLfloat ambient[] = { .1f, .1f, .1f, 1.0f};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat pos0[] = {1.0, 1.0, 1.0, 0.0};  // Infinite light location.

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
	glEnable(GL_LIGHT0);
	//cout<<"light enabled ";

}

//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport(0,0,viewport.w,viewport.h);// sets the rectangle that will be the window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // loading the identity matrix for the screen
  //gluPerspective (80, (float )w /(float)h, 1.0,5000.0 );
  glOrtho(-15,15,-15,15,-15,15);
  
  }

//****************************************************
//Update the rendering
//***************************************************
void Update()
{
    glScaled(scale, scale, 1.0);
	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);
	glTranslatef(tx, ty, 0);
	glTranslatef(0,0,zoom);
}


//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);				// clear the buffer

 glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
 glLoadIdentity();	                            // make sure transformation is "zero'

 initLights();

 if(!wireframe_only) {
	 if(smooth_shading){
		 glShadeModel(GL_SMOOTH);
	 } else {
		 glShadeModel(GL_FLAT);
	 }
 }
 
  Update();

  // time the rendering simulation
	clock_t start_time=clock();
	render();
    clock_t end_time=clock();
    cout<< "Running time is: "<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC<<"sec"<<endl;//output of the simulation time

	
    glFlush();
    glutSwapBuffers();                           // swap buffers (we earlier set double buffer)

}


//****************************************************
// function that handles keyboard input
//***************************************************
void myKeyHandler(unsigned char key, int x, int y) {
  //space to exit
  if(key == 32) {
    exit(0);
  } else if(key == 119) { //w
    wireframe_only = !wireframe_only;
  } else if(key == 115) { //s
    smooth_shading = !smooth_shading;
  } else if(key == 104) { //h
    hidden_line = !hidden_line;
  } else if(key == 43) { //+
	  scale*=1.1;
	  zoom+=0.2;
  } else if(key == 45) { //-
	  scale/=1.1;
	  zoom-=0.2;
  } else if(key == 61) { //=
    Update(); //identity
  }
  
  glutPostRedisplay();
}

void specialKeyHandler(int key, int x ,int y) {
  
	int mod = glutGetModifiers();

    if(mod % 2) { //shift, translate
    if(key == GLUT_KEY_UP) {
      tx-=1.0f;
    } else if(key == GLUT_KEY_DOWN) {
      tx+=1.0f;
    } else if(key == GLUT_KEY_LEFT) {
      ty-=1.0f;
    } else if(key == GLUT_KEY_RIGHT) {
      tx+=1.0f;
    }
  } else { //no shift, rotate
    if(key == GLUT_KEY_UP) {
      rotx-=5.0f;
    } else if(key == GLUT_KEY_DOWN) {
      rotx+=5.0f;
    } else if(key == GLUT_KEY_LEFT) {
      roty+=5.0f;
    } else if(key == GLUT_KEY_RIGHT) {
      roty-=5.0f;
    }

  }

  glutPostRedisplay();
}


//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Voronoi Cells of Spheres");
  initScene();							// quick function to set up scene
  glutDisplayFunc(myDisplay);				// function to run when its time to draw something
  glutReshapeFunc(myReshape);				// function to run when the window gets resized
 
  glutKeyboardFunc(myKeyHandler);       // function to handle key events. space to exit
  glutSpecialFunc(specialKeyHandler);    // arrow keys

  glutMainLoop();							// infinite loop that will keep drawing and resizing

  return 0;
}
