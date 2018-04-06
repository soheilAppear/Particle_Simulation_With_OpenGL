/********************************************************************************
*********************************************************************************
*                                                                               *
*                                                                               *
*************     Developed By Soheil Sephayar Summer of 2017       *************
*                                                                               *
*               Emails :    Soh.sepahyar.en@iauctb.ac.ir                        *
*                           soheil.appear@gmail.com                             *
*                                                                               *
*************************     Particles.h      **********************************
*                                                                               *
*                                                                               *
*********************************************************************************
********************************************************************************/

/* Particle Class that i had created for the basic and advanced feature of each particle in the project*/


#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <ctime>

using namespace std;

#pragma once  // It reduces possibilities for bugs.

//#define MAX_PARTICLES 10000   // the  number of particles at first

int particlesCurrentQuantity = 20000;

int maxParticlesQuantity = 20000;

int minParticlesQuantity = 0;

typedef float fVector[3];  // for three dimention we use three parameters

bool changinSize = false;

enum dimensions {X,Y,Z};

enum type { Regular=1 , Fountain=2 , Fire=3, FireWithSmoke=4 };



struct Particle
{
   int type; //used only for "fire with smoke" to tell between fire and smoke 0=fire, 1=smoke, 2=other

   float lifespan, age, scale, direction; // how long the particle will exist for, alpha blending variable; how old is it.


   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


   fVector position; // initial onscreen position   ====> It relates to the emitter.

   fVector movement; // movement vector

   fVector color; // color values

   fVector pull; // compounding directional pull in the x,y,z directions We use this variable for our movement with keyboard

}; 

Particle * particles = new Particle[particlesCurrentQuantity];

class System
{

   int systemType; //1 = regular, 2 = fountain, 3 = fire , 4 = fireWithSmoke

   fVector systemPull; //used to store global compounding system pull in x,y,z

   //Particle particles[MAX_PARTICLES]; //initalizes and array of type Particle    page 480 Edward Angel

public:

	

   void createParticle(Particle *p); //creates and initalizes a single particle

   void createParticles(); //calls createParticle() to initalize all particles in system

   void updateParticles(); //updates particles according to forces being used

   void turnToSmoke(Particle *p); //called only durring fire with smoke system to turn dead fire into smoke

   void setSystemType(int systemType); //sets the particle system type

   int getNumOfParticles(); // returns the number of particles in the system (legacy)

   ~System(void);  // Destructor



   float getXPos(int i); //returns x position of particle i
   float getYPos(int i); //returns y position of particle i
   float getZPos(int i); //returns z position of particle i
   float getR(int i); //returns red component of particle i
   float getG(int i); //returns green component of particle i
   float getB(int i); //returns blue component of particle i
   float getScale(int i); //returns scale of particle
   float getDirection(int i); //returns direction of particle for texture rotation
   float getAlpha(int i); //returns how faded (according to age) the particle should be

   void modifySystemPull(float x, float y, float z); //used to modify x,y,z pull magnitudes

	
   void OnMouseClick(int button, int state, int x, int y); 
   void handleKeypress2(unsigned char key2, int x, int y);

};



void System::createParticle(Particle *p)
{
  

   if(systemType == Fire || systemType == FireWithSmoke)
   {
      p->lifespan = ((( rand() % 20 + 1 ))) /10.0;

      if(systemType == FireWithSmoke)
	  {
         p->type = 0;
	  }
   }

   else
   {
      p->lifespan = ((( rand() % 125 + 1 ) / 10.0 ) + 5);
      p->type = 2;
   }

   p->age = 0.0;
   p->scale = 0.25;
   p->direction = 0;
   
   if(systemType == Regular || systemType == Fire || systemType == FireWithSmoke || systemType == Fountain)
   {
      p->position[X] = (rand() % 30);  // for specifying number of emmiters  
   }

   else
   {
	 p->position[X] = 0;
   }

   if(systemType == Regular)
   {
      p->position[Y] = -30;
   }

   else
   {
      p->position[Y] = -15;
   }

   p->position[Z] = 0;

   if(systemType == Regular)
   {
      p->movement[X] = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.007) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.007);   
      p->movement[Y] = ((((((5) * rand()%11) + 5)) * rand()%11) + 1) * 0.02;
      p->movement[Z] = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.007) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.007);
   }

   else if(systemType == Fountain)
   {
      p->movement[X] = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.005) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.005);   
      p->movement[Y] = ((((((5) * rand()%11) + 5)) * rand()%11) + 10) * 0.02;
      p->movement[Z] = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.005) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.005);
   }

   else 
   { 
      p->movement[X] = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.005) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.005);   
      p->movement[Y] = ((((((5) * rand()%11) + 5)) * rand()%11) + 1) * 0.02;
      p->movement[Z] = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.005) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.005);
   }

   if(systemType == Regular)
   {//greyish-white for regular mode
      p->color[X] = -1;
      p->color[Y] = 0.7;
      p->color[Z] = 0.7111;
   }

   else if(systemType == Fountain)
   {//blue for water
      p->color[X] = 0.0;
      p->color[Y] = 0.0;
      p->color[Z] = 1.0;
   }

   else if(systemType == Fire || systemType == FireWithSmoke)
   {//red with mix of yellow for fire
      p->color[X] = 1.0;
      p->color[Y] = 0.95;
      p->color[Z] = 0.8;
   }

   p->pull[X] = 0.0;
   p->pull[Y] = 0.0;
   p->pull[Z] = 0.0;

}


void System::createParticles(void)
{
   if(systemType == Fountain)
   {
      systemPull[Y] = -0.0025;
      systemPull[X] = systemPull[Z] = 0.0;
   }

   else if(systemType == Fire)
   {
      systemPull[Y] = 0.01;  // for changing the height of our fire. and with keyboard we can increase or decrease it.
      systemPull[X] = systemPull[Z] = 0.0;
   }

   else if(systemType == FireWithSmoke)
   {
      systemPull[Y] = 0.0005;
      systemPull[X] = systemPull[Z] = 0.0;
   }

   else
   {
      systemPull[X] = systemPull[Y] = systemPull[Z] = 0.0;
   }

   int i = 0;

   for(i; i < /*MAX_PARTICLES*/ particlesCurrentQuantity ; i++)
   {
   			createParticle(&particles[i]);	  
   }

}


void System::updateParticles(void)
{
   int i = 0;
   for(i; i < /*MAX_PARTICLES*/  particlesCurrentQuantity ; i++)
   {
      particles[i].age = particles[i].age + 0.02; // This + 0.2 is for dying the particles at the end of the screen and their pathes.
      
      if(systemType == Regular || particles[i].type == 1)
         particles[i].scale = particles[i].scale + 0.001; //increasing scale makes textures bigger over lifetime

      particles[i].direction = particles[i].direction + ((((((int)(0.5) * rand()%11) + 1)) * rand()%11) + 1);  // for rotation of the particles


      particles[i].position[X] = particles[i].position[X] + particles[i].movement[X] + particles[i].pull[X];
      particles[i].position[Y] = particles[i].position[Y] + particles[i].movement[Y] + particles[i].pull[Y];
      particles[i].position[Z] = particles[i].position[Z] + particles[i].movement[Z] + particles[i].pull[Z];
      
      particles[i].pull[X] = particles[i].pull[X] + systemPull[X];
      particles[i].pull[Y] = particles[i].pull[Y] + systemPull[Y]; // acleration due to gravity
      particles[i].pull[Z] = particles[i].pull[Z] + systemPull[Z];
	



      // color changing for fire particles light yellow -> red with age
      if(systemType == Fire || particles[i].type == 0)
      {
         float temp = particles[i].lifespan/particles[i].age;    // hargheghadr ziyad tar bashad in kasr yaani omre particle kamtar hastesh tush. rang ra ham bar hamin asas ebtekhab mikonand.

         if((temp) < 1.75)
         {//red

            particles[i].color[X] = 1.0;
            particles[i].color[Y] = 0.25;
            particles[i].color[Z] = 0.0;

         }

         else if((temp) < 3.0)
         {//gold
            particles[i].color[X] = 1.0;
            particles[i].color[Y] = 0.9;
            particles[i].color[Z] = 0.0;
         }

         else if((temp) < 10.0)
         {//yellow
            particles[i].color[X] = 1.0;
            particles[i].color[Y] = 1.0;
            particles[i].color[Z] = 0.0;
         }

         else
         {// initial light yellow
            particles[i].color[X] = 1.0;
            particles[i].color[Y] = 0.95;
            particles[i].color[Z] = 0.8;
         }
      }


      if(systemType == Regular)
      {
         if (particles[i].age > particles[i].lifespan || particles[i].position[Y] > 45 || particles[i].position[Y] < -35 || particles[i].position[X] > 80 || particles[i].position[X] < -80)
            createParticle(&particles[i]);
      }
      else if(systemType == Fountain)
      {
         if (particles[i].position[Y] > 35 || particles[i].position[Y] < -25 || particles[i].position[X] > 40 || particles[i].position[X] < -40)
            createParticle(&particles[i]);
      }
      else if(systemType == Fire)
      {
         if (particles[i].age > particles[i].lifespan || particles[i].position[Y] > 35 || particles[i].position[Y] < -25 || particles[i].position[X] > 40 || particles[i].position[X] < -40)
            createParticle(&particles[i]);
      }


	  else if(systemType == FireWithSmoke)
      {
         if(particles[i].type == 0)
         {
            if (particles[i].age > particles[i].lifespan || particles[i].position[Y] > 35 || particles[i].position[Y] < -25 || particles[i].position[X] > 40 || particles[i].position[X] < -40)
            {
               int temp = rand()%100;

               if(temp < 10)
			   {
                  turnToSmoke(&particles[i]);
			   }

               else
			   {
                  createParticle(&particles[i]);
			   }
            }
         }

         else if(particles[i].type == 1)
         {
            if (particles[i].age > particles[i].lifespan || particles[i].position[Y] > 45 || particles[i].position[Y] < -35 || particles[i].position[X] > 80 || particles[i].position[X] < -80)
               createParticle(&particles[i]);
         }     
	  }
   }
}


void System::turnToSmoke(Particle *p)
{
   p->lifespan = (((rand()%125+1)/10.0f)+5);
   p->age = 0.0f;
   p->scale = 0.25f;
   p->direction = 0;
   p->type = 1;

   p->movement[X] = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.0035) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.0035);
   p->movement[Y] = ((((((5) * rand()%11) + 3)) * rand()%11) + 7) * 0.015; 
   p->movement[Z] = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.0015) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.0015);

   p->color[X] = 0.7;
   p->color[Y] = 0.7;
   p->color[Z] = 0.7;
}

void System::setSystemType(int type)
{
   systemType = type;
}

int System::getNumOfParticles(void)
{
   return /*MAX_PARTICLES*/  particlesCurrentQuantity ;
}

float System::getXPos(int i)
{
   return particles[i].position[X];
}

float System::getYPos(int i)
{
   return particles[i].position[Y];
}
float System::getZPos(int i)
{
   return particles[i].position[Z];
}

float System::getR(int i)
{
   return particles[i].color[X];
}

float System::getG(int i)
{
   return particles[i].color[Y];
}

float System::getB(int i)
{
   return particles[i].color[Z];
}

float System::getScale(int i)
{
   return particles[i].scale;
}

float System::getDirection(int i)
{
   return particles[i].direction;
}

float System::getAlpha(int i) // We use this for have the especial life of our particles.
{
   return (1 - particles[i].age/particles[i].lifespan);
}

void System::modifySystemPull(float x, float y, float z)   // we use += x for increasing or decreasing the height of our particles.
{
   systemPull[X] += x;
   systemPull[Y] += y;
   systemPull[Z] += z;
   
}


System::~System(void)
{
	cout << "Particles are dead and Memory has been released!"<<endl;
	delete particles;
}


void OnMouseClick(int button, int state, int x, int y)
{
	
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && particlesCurrentQuantity < maxParticlesQuantity) 
		{ 
			
			particlesCurrentQuantity = particlesCurrentQuantity + 10;
			cout << "Left click with Mouse!\n";
			cout<< "Number of Particle is : " << particlesCurrentQuantity <<endl;

		}	

		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && particlesCurrentQuantity < maxParticlesQuantity) 
		{ 
			
			particlesCurrentQuantity = particlesCurrentQuantity + 10;
			cout << "Left click with Mouse!\n";
			cout<< "Number of Particle is : " << particlesCurrentQuantity <<endl;

		}	


		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN  && particlesCurrentQuantity > minParticlesQuantity ) 
		{ 
			
			particlesCurrentQuantity = particlesCurrentQuantity - 10;
			cout << "Right click with Mouse!\n";
			cout<< "Number of Particle is : " << particlesCurrentQuantity <<endl;			 
		} 

}