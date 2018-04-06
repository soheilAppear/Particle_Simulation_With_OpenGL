/********************************************************************************
*********************************************************************************
*                                                                               *
*                                                                               *
*************     Developed By Soheil Sephayar Summer of 2017       *************
*                                                                               *
*               Emails :    Soh.sepahyar.en@iauctb.ac.ir                        *
*                           soheil.appear@gmail.com                             *
*                                                                               *
*************************       Main.cpp        *********************************
*                                                                               *
*                                                                               *
*********************************************************************************
********************************************************************************/




/* Main Class For Using the Particle.h that i had created before */


#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <conio.h>

#include "Particles.h"

using namespace std;

GLfloat zoom;
GLfloat zoomSize = -80;

System particleSystem;

GLfloat particleSize = 0.5;

GLint shapeChoise = 0;  // 0 is quad, 1 is triangle. and 2 is sphere and ...

void DrawParticles (void)
{
   int i;

   for (i = 1; i < particleSystem.getNumOfParticles(); i++)
   {
      glPushMatrix();

      // set color and fade value (alpha) of current particle
      glColor4f(particleSystem.getR(i), particleSystem.getG(i), particleSystem.getB(i), particleSystem.getAlpha(i));

      // move the current particle to its new position
      glTranslatef(particleSystem.getXPos(i), particleSystem.getYPos(i), particleSystem.getZPos(i)  + zoom);

      // rotate the particle (this is proof of concept for when proper smoke texture is added)
      glRotatef (particleSystem.getDirection(i) - 90, 0, 0, 1);

      // scale the wurrent particle (only used for smoke)
      glScalef(particleSystem.getScale(i), particleSystem.getScale(i), particleSystem.getScale(i));
	  
	  if (shapeChoise == 0)  // Q key
	  {
			glBegin (GL_QUADS);
 
			glVertex3f (-particleSize, -particleSize, 0);
			glVertex3f (particleSize, -particleSize, 0);
			glVertex3f (particleSize, particleSize, 0);
			glVertex3f (-particleSize, particleSize, 0);
      
			glEnd();
	  }

	  else if (shapeChoise == 1)  // T key
	  {
		    glBegin (GL_TRIANGLES);
			glVertex3f (-particleSize, -particleSize, 0);
			glVertex3f (particleSize, -particleSize, 0);
			glVertex3f (particleSize, particleSize, 0);
	  }

	  else if (shapeChoise == 2) // S key
	  {
			glutWireSphere(particleSize, 50, 50);		
	  }

	  else if (shapeChoise == 3)   //W key
	  {
			glutWireTorus( /* inner r*/ 4, /*outer r*/ particleSize, /*slices*/ 14, /* rings */ 9)	;
	  }

	  else if (shapeChoise == 4)  // E key
	  {
			glutWireTetrahedron();	
	  }

	  else if (shapeChoise == 5) // C key
	  {
			glutWireCube(particleSize);
	  }

	  else if (shapeChoise == 6)  // R key
	  {
			glutWireTeapot(particleSize);		
	  }


	  glEnd();
      glEnable(GL_DEPTH_TEST);
      glPopMatrix();
   }
}

void display (void)
{
   glClearDepth (1);
   glClearColor (0.0,0.0,0.0,1.0);
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();  
   glTranslatef (0,0,-10);
   particleSystem.updateParticles();
   DrawParticles();
   glutSwapBuffers();
}

void init (void)
{
	glEnable(GL_DEPTH_TEST);
    zoom = -80.0; // we use zoom out to see the particles movements
   particleSystem.setSystemType(1);
   particleSystem.createParticles();
}

void opacityInit()   // opacity changing rendering
{
	glEnable(GL_BLEND);
	zoom = -80.0; // we use zoom out to see the particles movements
    particleSystem.setSystemType(1);
    particleSystem.createParticles();
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glutSwapBuffers();
	glLoadIdentity();
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
   {
      case 49: //1 key: smoke
		 cout << "Starting the first particles program!!"<< endl <<endl;
         zoom = -80.0;
         particleSystem.setSystemType(1);
         particleSystem.createParticles();
		 
         break;

      case 50: //2 key: fountain high
		 cout << "Starting the Fountain particles program!!"<< endl <<endl;
         zoom = -40.0;
         particleSystem.setSystemType(2);
         particleSystem.createParticles();
         break;

      case 51: //3 key: fire
		 cout << "Starting the Fire particles program!!"<< endl <<endl;
         zoom = -40.0;
         particleSystem.setSystemType(3);
         particleSystem.createParticles();
         break;

	  case 52: //4 key: fireWithSmoke
		 cout << "Starting the Fire particles program!!"<< endl <<endl;
         zoom = -40.0;
         particleSystem.setSystemType(4);
         particleSystem.createParticles();
         break;

      case 61: //+ key: change x pull for more wind to right
		 cout << "Increasing the wind to the right sides of the particles.." << endl <<endl;
         particleSystem.modifySystemPull(0.0005, 0.0, 0.0);
         break;

      case 45: //- key: change x pull for wind wind to left
		 cout << "Increasing the wind to the left sides of the particles.." << endl <<endl;
         particleSystem.modifySystemPull(-0.0005, 0.0, 0.0);
         break;

      case 91: //[ key: change y pull for less gravity
		 cout << "Decreasing gravity for the particles.."<< endl <<endl;
         particleSystem.modifySystemPull(0.0, 0.0005, 0.0);
         break;

      case 93: //] key; change y pull for more gravity
		 cout << "Increasing gravity for the particles.."<< endl <<endl;
         particleSystem.modifySystemPull(0.0, -0.0005, 0.0);
         break;

	  case 104: // h baraye ziyad kardane size particle ha be soorate dynamic
		 cout << "Increasing the particle sizes.."<< endl <<endl;
         particleSize += 0.08;
		 break;

	  case 72: // H baraye ziyad kardane size particle ha be soorate dynamic
		 cout << "Increasing the particle sizes.."<< endl <<endl;
         particleSize += 0.08;
		 break;

	  case 108: // l baraye kam kardane size particle ha be soorate dynamic
		 cout << "Decreasing the particle sizes.."<< endl <<endl;
         particleSize -= 0.08;
		 break;

	  case 76: // l baraye kam kardane size particle ha be soorate dynamic
		 cout << "Decreasing the particle sizes.."<< endl <<endl;
         particleSize -= 0.08;
         break;

	  case 113: // entekhabe Quad baraye particle
		cout << "Choosing the Quad particles.." << endl << endl;
         shapeChoise = 0;
         break;

	  case 81: // entekhabe Quad baraye particle
		 cout << "Choosing the Quad particles.." << endl << endl;
         shapeChoise = 0;
         break;


	  case 84: // entekhabe Triangle baraye particle
		 cout << "Choosing the Triangle particles.." << endl << endl;
         shapeChoise = 1;
         break;

	  case 116: // entekhabe Triangle baraye particle
		 cout << "Choosing the Triangle particles.." << endl << endl;
         shapeChoise = 1;
         break;

	  case 115: // entekhabe Sphere baraye particle
		 cout << "Choosing the Sphere particles.." << endl << endl;
         shapeChoise = 2;
         break;

	  case 83: // entekhabe Sphere baraye particle
		 cout << "Choosing the Sphere particles.." << endl << endl;
         shapeChoise = 2;
         break;

	  case 119: // entekhabe Torus baraye particle
		 cout << "Choosing the Torus particles.." << endl << endl;
         shapeChoise = 3;
         break;

	  case 101: // entekhabe Tetrahedran baraye particle
		 cout << "Choosing the Tetrahedran particles.." << endl << endl;
         shapeChoise = 4;
         break;


	  case 99: // entekhabe Cube baraye particle
		 cout << "Choosing the Cube particles.." << endl << endl;
         shapeChoise = 5;
         break;

	  case 114: // entekhabe Teapot baraye particle
		 cout << "Choosing the Teapot particles.." << endl << endl;
         shapeChoise = 6;
         break;


		case 27: //Escape key
			cout << "Exiting.." << endl << endl;
			exit(0);
			delete particles;  // For releasing the Memory that used by particles.
			
	}	
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);   //baraye tanzime safheye namayeshgar hastesh ke agar bozorg shod be moshkeli bar nakhordad
	zoom = zoomSize;
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char **argv)
{
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize (1000, 1000);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Particle System");
   init();
   glutDisplayFunc (display);
   glutIdleFunc (display);
   glutReshapeFunc (reshape);
   opacityInit();
   glutDisplayFunc (display);
   glutIdleFunc (display);
   // Keyboard Functions
   glutKeyboardFunc(handleKeypress);
   glutMouseFunc(OnMouseClick);
   glutReshapeFunc (reshape);
   glutMainLoop ();

   return 0;
}

