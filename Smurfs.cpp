//-----------------------------------------------------------------------
//      File:           smurfs.cpp
//      Description:    A sample OpenGL program
//      Programmer:     Dave Mount
//      For:            CMSC 427 - Computer Graphics
//      Date:           Fall 2011
//
//      This is just a sample skeleton C++ program, which shows the
//      general structure of a minimal OpenGL program.
//-----------------------------------------------------------------------
#include "RGBpixmap.h"

#include <cstdlib>                      // standard definitions
#include <iostream>                     // C++ I/O
#include <cstdio>                       // C I/O (for sprintf) 
#include <cmath>                        // standard definitions
#include <math.h>
#include <list>

#include <GL/glut.h>                    // GLUT
#include <GL/glu.h>                     // GLU
#include <GL/gl.h>                      // OpenGL

#include <ostream>
#include <sys/timeb.h>



#define PI 3.14159265358979
#define MAX_Z 30

GLint TIMER_DELAY = 10; // timer delay (10 seconds) 
// angle of rotation for the camera direction
float angle=0.0f;
// actual vector representing the camera’s direction
float lx=0.0f,ly=1.0f;
// XZ position of the camera
float x=0.0f,y=-5.0f;
float mouseX = 0.0f;
float mouseY = 0.0f;
bool gameover = false;
bool win = false;
double rm = double(RAND_MAX); 
int spawnCount = 0;


void drawBody(float x, float y, float z, float armAngle, float footDelta, float bodyRotate) {
	
	
	// Draw Body
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f , 0.0f, 0.75f);
	glScalef(0.5f, .5f, .95f);
	glutSolidSphere(0.75f,20,20);
	glPopMatrix();
	
	// Draw Head
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, 1.75f);
	glScalef(2.0f, 1.0f, 1.0f);
	glutSolidSphere(0.25f,20,20);
	glPopMatrix();
	
	//draw feet
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef((-.3f), (-.3f+footDelta), (0.2f));
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidSphere(0.2f, 20, 20);
	glPopMatrix();
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef((.3f), (-.3f-footDelta), (0.2f));
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidSphere(0.2f, 20, 20);
	glPopMatrix();

	//draw arms
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef((-.5f), (0), (0.8f));
	glRotatef(armAngle, 1, 0, 0);
	glRotatef(20.0f, 0, 1, 0);
	glScalef(1.0f, 1.0f, 2.0f);
	glutSolidSphere(0.2f, 20, 20);
	glPopMatrix();
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef((.5f), (0), (0.8f));
	glRotatef(-1.0f*armAngle, 1, 0, 0);
	glRotatef(-20.0f, 0, 1, 0);
	glScalef(1.0f, 1.0f, 2.0f);
	glutSolidSphere(0.2f, 20, 20);
	glPopMatrix();

}

void drawBodyZ(float x, float y, float z, float armAngle, float footDelta, float bodyRotate, float spawnAngle) {
	
	
	// Draw Body
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glRotatef(spawnAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f , 0.0f, 0.75f);
	glScalef(0.5f, .5f, .95f);
	glutSolidSphere(0.75f,20,20);
	glPopMatrix();
	
	// Draw Head
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glRotatef(spawnAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 1.75f);
	glScalef(2.0f, 1.0f, 1.0f);
	glutSolidSphere(0.25f,20,20);
	glPopMatrix();
	
	//draw feet
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glRotatef(spawnAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef((-.3f), (-.3f+footDelta), (0.2f));
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidSphere(0.2f, 20, 20);
	glPopMatrix();
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glRotatef(spawnAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef((.3f), (-.3f-footDelta), (0.2f));
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidSphere(0.2f, 20, 20);
	glPopMatrix();

	//draw arms
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glRotatef(spawnAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef((-.5f), (0), (0.8f));
	glRotatef(armAngle, 1, 0, 0);
	glRotatef(20.0f, 0, 1, 0);
	glScalef(1.0f, 1.0f, 2.0f);
	glutSolidSphere(0.2f, 20, 20);
	glPopMatrix();
	glPushMatrix();
	//glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(bodyRotate, 0.0f, 0.0f, 1.0f);
	glRotatef(spawnAngle, 1.0f, 0.0f, 0.0f);
	glTranslatef((.5f), (0), (0.8f));
	glRotatef(-1.0f*armAngle, 1, 0, 0);
	glRotatef(-20.0f, 0, 1, 0);
	glScalef(1.0f, 1.0f, 2.0f);
	glutSolidSphere(0.2f, 20, 20);
	glPopMatrix();

}



int getMilliCount()
{
  // Something like GetTickCount but portable
  // It rolls over every ~ 12.1 days (0x100000/24/60/60)
  // Use GetMilliSpan to correct for rollover
  timeb tb;
  ftime( &tb );
  int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
  return nCount;
}

int getMilliSpan( int nTimeStart )
{
  int nSpan = getMilliCount() - nTimeStart;
  if ( nSpan < 0 )
    nSpan += 0x100000 * 1000;
  return nSpan;
}

class Smurf{
	float oX;
	float oY;
	float z;
	
	private:
		float vV;
		float hV;
		float phX;
		float phY;
		float bodyAngle;
		float friction;
		float gravity;
		float dTimeXY;
		float dTimeZ;
		float armAngle;
		int aD;
		float footDelta;
		int fD;
		bool jump;
		bool move;
		bool fall;
		float fallAngle;
	public:
		Smurf(float, float, float);
		float getX(){
			return oX;
		}	
		float getY(){
			return oY;
		}
		float getZ(){
			return z;
		}
		void hasJumped(){
			jump = true;
		}
		void hasMoved(float dx, float dy){
			if (!jump && !fall && !gameover){
				float lm = sqrt(phX*phX+phY*phY);
				if (lm > 10.0f){
					lm = 10.0f/lm;
					dx *= lm;
					dy *= lm;
				}
				phX += dx*hV;
				phY += dy*hV;
				//printf("dx %f dy %f\n", phX, phY);

// 				armAngle += (aD*10.0);
// 				if (armAngle > 80 || armAngle < -80){
// 					aD *= -1;
// 				}
				
				bodyAngle = atan2(dy,dx)*180/PI+90;
				
			}
					
				
		}
		void moveZ(double elapsedTime){
			if (!win && !gameover){
				if (jump && !fall){
					vV -= gravity*elapsedTime;
					z += vV;
					oX += phX*elapsedTime;
					oY += phY*elapsedTime;
					dTimeZ += .1;
					if (z <= 0){
						z = 0;
						jump = false;
						dTimeZ = 0.0f;
						vV = .40f;
					}
				}
				else if (fall){
					vV += gravity*elapsedTime;
					z -= vV;
					dTimeZ += .1;
					armAngle = 180;
					fallAngle += 120.0f*elapsedTime;
					if (fallAngle >= 180.0f){
						fallAngle = 1800.0f;
					}
					if (z < -40){
						gameover = true;
					}
				}
			}
			else if (win){
				vV -= gravity*elapsedTime;
				z += vV;
				dTimeZ += .1;
				if (z <= 0){
					z = 0;
					dTimeZ = 0.0f;
					vV = .4f;
				}
			}	
				
		}
		void moveXY(double elapsedTime){
			if (!win && !gameover){
				if (fall){
					oX += phX*elapsedTime; //times elapsed time
					oY += phY*elapsedTime; //times elapsed time
				}
				else if (!jump){
					phX = (friction*phX);
					phY = (friction*phY);
					if (phX < .01f && phX > -.01f && phY < .01f && phY > -.01f){
						phX = 0;
						phY = 0;
						armAngle = 0.0f;
						footDelta = 0.0f;
					}
	// 				printf("elapsedTime %f\n", elapsedTime);
	// 				printf("phX %f phY %f\n", phX, phY);
					oX += phX*elapsedTime; //times elapsed time
					oY += phY*elapsedTime; //times elapsed time
					armAngle += (sqrt(phX*phX+phY*phY)*aD*1.0);
					if (armAngle > 80 || armAngle < -80){
						aD *= -1;
					}
					footDelta += (sqrt(phX*phX+phY*phY)*fD*.010);
					if (footDelta > .2f || footDelta < -.2f){
						fD*= -1;
					}
					
					if (oX >= 30.25 || oX < -30.25 || oY >= 30.25 || oY <= -30.25){
						fall = true;
					}
				}
			}
		}
		bool tfFall(){
			return fall;
		}
		bool tfJump(){
			return jump;
		}
		void draw(){
			glPushMatrix();
			//glTranslatef(oX, oY, z);
			drawBodyZ(oX, oY, z, armAngle, footDelta, bodyAngle, fallAngle);
			glPopMatrix();
		}
};

Smurf::Smurf(float x, float y, float altitude){
			oX = x;
			oY = y;
			z = altitude;

			hV = .4f;
			phX = 0.0f;
			phY = 0.0f;
			bodyAngle = 0.0f;
			vV = .4f;
			friction = .95f;
			gravity = .75f;
			jump = false;
			fall = false;
			dTimeXY = 0.0f;
			dTimeZ = 0.0f;

			armAngle = 0.0f;
			aD = 1;
			footDelta = 0.0f;
			fD = 1;

			fallAngle = 0.0f;
		}
static Smurf player(0.0f, 0.0f, 0.0f);

class Zombie{
	float x;
	float y;
	float z;
	float speed;
	float angle;
	float vectorX;
	float vectorY;
	bool fall;
	float armAngle;
	int aD;
	float footDelta;
	int fD;
	bool spawn;
	float spawnAngle;
	public:
		Zombie(float ox, float oy, float a){
			x = ox;
			y = oy;
			z = 0.0f;
			speed = .1;
			angle = a;
			fall = false;
			vectorX = sin(PI/180*a);
			vectorY = -cos(PI/180*a);

			armAngle = 0.0f;
			aD = 1;
			footDelta = 0.0f;
			fD = 1;
			spawn = true;
			spawnAngle = 90.0f;
		}
		
		float getZ(){
			return z;
		}
		
		void spawnZombie(double elapsedTime){
			if (spawn){
				spawnAngle -= 20.0f*elapsedTime;
				if (spawnAngle <= 0.0f){
					spawnAngle = 0.0f;
					spawn = false;
				}
			}
		}
		
		void rotate(double elapsedTime){
			if (!fall && !spawn){
				float dy = player.getY() - y;
				float dx = player.getX() - x;
				float l = sqrt(dx*dx + dy*dy);
				//normalize
				dx /= l;
				dy /= l;
				float theta = atan2(dx, -dy);
				theta *= 180/PI;
				
				float temp = theta - angle;
				if ((temp > -180 && temp < 0) || (temp > 180 && temp < 360)){
					angle -= 1.5f*elapsedTime;
				}
				else if ((temp > -360 && temp <= -180) || (temp > 0 && temp <= 180)){
					angle += 1.5f*elapsedTime;
				}
				vectorX = sin(PI/180*angle);
				vectorY = -cos(PI/180*angle);
			}
		}
		
		void move(double elapsedTime){
			if (!spawn){
				float l = sqrt(vectorX*vectorX + vectorY*vectorY);
				float vx = vectorX/l;
				float vy = vectorY/l;
				x += .25*vx*elapsedTime;
				y += .25*vy*elapsedTime;
				
				armAngle += (sqrt(vx*vx+vy*vy)*aD*.20);
				if (armAngle > 80 || armAngle < -80){
					aD *= -1;
				}
				footDelta += (sqrt(vx*vx*vy*vy)*fD*.010);
				if (footDelta > .2f || footDelta < -.2f){
					fD*= -1;
				}
				if (x >= 15 || x < -15 || y >= 15 || y <= -15){
					fall = true;
				}
				if (fall){
					z -= 8.0*elapsedTime;
					spawnAngle += 120.0f*elapsedTime;
					if (spawnAngle >= 180.0f){
						spawnAngle = 1800.0f;
					}
				}
			}
				
		}
		
		void draw(){
			glPushMatrix();
			glTranslatef(x, y, z);
			//glRotatef(angle, 0, 0, 1);
			drawBodyZ(x,y,z, armAngle, footDelta, angle, spawnAngle);
			glPopMatrix();
		}
		
		void checkCollision(){
			double sr = sqrt((x-player.getX()/2)*(x-player.getX()/2)+(y-player.getY()/2)*(y-player.getY()/2));
			bool j = player.tfJump();
			
			if (sr <= .4 && !j && !spawn){
				gameover=true;
			}
		}
};

list<Zombie> zList;


class Camera{
	float x, originX;
	float y, originY;
	float z, originZ;
	float axy;
	float az;
	float zoom;
	float tempT;
	float tempP;
	public:
		Camera(float, float, float, float, float);
		float getX(){
			return x;
		}				
		float getY(){
			return y;
		}
		float getZ(){
			return z;
		}	
		void saveAngles(){
			tempT = axy;
			tempP = az;
		}
		float getAXY(){
			return axy;
		}
		float getAZ(){
			return az;
		}
		void changeAngleT(float dT){
			axy = tempT + (.36f*dT);
			if (axy >= 360){
				axy -= 360.0f;
			}
			else if (axy <= -360){
				axy += 360.f;
			}
			setCamera();
		}
		void changeAnglePhi(float dP){
			if ((tempP+(.36f*dP)) <= 85 && (tempP+(.36f*dP)) >= 0){
				az = tempP+(.36f*dP);
			}
			setCamera();
		}
		void zoomIn(){
			zoom *= .95f;
			if (zoom < 0.001f){
				zoom = 0.001f;
			}
			setCamera();
		}
		void zoomOut(){
			zoom *= 1.05f;
			if (zoom > 200){
				zoom = 200.0f;
			}
			setCamera();
		}
		void setCamera(){
			//x = x*cos(a);
			// Add lift
			x = zoom * cos(3.14159/180*(az)) * cos(3.14159/180*(axy)) + player.getX();
			y = zoom * cos(3.14159/180*(az)) * sin(3.14159/180*(axy)) + player.getY();
			z = zoom * sin(3.14159/180*(az));
		}
			 
};



void drawTile(float xMove, float yMove){
	glColor3f(.2f, .2f, .4f);
	//Draw Six Sides
	glPushMatrix();
	
	glTranslatef(xMove, yMove, 0.0f);
	glBegin(GL_POLYGON); //top
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-2.5f, 2.5f, 0.0f);	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-2.5f, -2.5f, 0.0f);	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(2.5f, -2.5f, 0.0f);	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(2.5f, 2.5f, 0.0f);
	glEnd();	
	glBegin(GL_POLYGON); //left face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, 0.0f);	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, -0.2f);	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.5f, 2.5f, -0.2f);	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.5f, 2.5f, 0.0f);
	glEnd();	
	glBegin(GL_POLYGON); //right face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, 0.0f);	
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-2.5f, 2.5f, 0.0f);	
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-2.5f, 2.5f, -0.2f);	
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, -0.2f);
	glEnd();	
	glBegin(GL_POLYGON);//bottom
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-2.5f, 2.5f, -0.2f);	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(2.5f, 2.5f, -0.2f);	
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(2.5f, -2.5f, -0.2f);	
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-2.5f, -2.5f, -0.2f);
	glEnd();	
	glBegin(GL_POLYGON);//back
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-2.5f, 2.5f, 0.0f);	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2.5f, 2.5f, 0.0f);	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2.5f, 2.5f, -0.2f);	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-2.5f, 2.5f, -0.2f);
	glEnd();	
	glBegin(GL_POLYGON);//front
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, 0.0f);	
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, -0.2f);	
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, -0.2f);	
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, 0.0f);
	glEnd();	
	glPopMatrix();

}

void drawTopGround(float xMove, float yMove){
	//glColor3f(.2f, .2f, .4f);
	//Draw Six Sides
// 	GLfloat color[4] = {0.5f, .5f, .5f, 1.0}; // gray
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
// 	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
 	glPushMatrix();
	
	glTranslatef(xMove, yMove, 0.0f);
	glBegin(GL_POLYGON); //top
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-2.5f, 2.5f, 0.0f);	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-2.5f, -2.5f, 0.0f);	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(2.5f, -2.5f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);	
	glVertex3f(2.5f, 2.5f, 0.0f);
	glEnd();	
	
	glPopMatrix();
}

void drawShadows(float vx, float vy, float vz){ //TODO fix shadow function
	GLfloat shadowMatrix[16] =	{1, 0, 0, 0,
					0, 1, 0, 0,
					((-1*vx)/vz), ((-1*vy)/vz), 0, 0,
					0, 0, 0, 1};
	GLfloat color[4] = {0.12, 2.0, 2.0, 1.0}; // gray
	//Draw visible ground to stencil buffer
	glDisable(GL_DEPTH_TEST);
 	glColorMask(0,0,0,0);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_STENCIL_TEST);
	for (int t1 = -5; t1 <=5; t1++){ 
		for (int t2 = -5; t2 <= 5; t2++){
			drawTopGround(5.5f*t1, 5.5f*t2);
		}
	}
 	glDisable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
 	glColorMask(1, 1, 1, 1);

	//Draw shadow
	for (int t1 = -5; t1 <=5; t1++){ 
		for (int t2 = -5; t2 <= 5; t2++){
			drawTopGround(5.5f*t1, 5.5f*t2);
		}
	}
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glEnable(GL_STENCIL_TEST);
	//draw shadows
	glMultMatrixf(shadowMatrix);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	//glDisable(GL_LIGHTING);
	//glPushMatrix();
	player.draw();
	//glPopMatrix();
	list<Zombie>::iterator z1;
	for (z1 = zList.begin(); z1!=zList.end(); ++z1){ 
		z1->draw(); 
	}
	//glEnable(GL_LIGHTING);
	//glPopMatrix();
	glDisable(GL_STENCIL_TEST);
}
	
	

RGBpixmap myPixmap;

void makeSkyBox(){
  
  //------------------------------------------------------------------
  // Read texture from a .bmp file (done once per texture file). The
  // file name is a path relative to the working directory where the
  // program runs.
  //
  // If you see the error message below, determine the working directory
  // in which your program executes, and set the path to the .bmp file
  // relative to this directory.
  //------------------------------------------------------------------
  if (!myPixmap.readBMPFile("skybox-clouds.bmp", true, true)) {
      printf("File skybox-clouds cannot be read or illegal format\n");
      exit(1);
  }
  
  //------------------------------------------------------------------
  //  OpenGL initializations (done once for each texture)
  //------------------------------------------------------------------
  GLuint texID;                               // OpenGL texture ID
  glGenTextures(1, &texID);                   // generate texture ID
  glBindTexture(GL_TEXTURE_2D, texID);        // set the active texture

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);      // store pixels by byte

  glTexImage2D(                               // present texture to OpenGL
      GL_TEXTURE_2D,                          // texture is 2-d
      0,                                      // resolution level 0
      GL_RGB,                                 // internal format
      myPixmap.nCols,                         // image width
      myPixmap.nRows,                         // image height
      0,                                      // no border
      GL_RGB,                                 // my format
      GL_UNSIGNED_BYTE,                       // my type
      myPixmap.pixel);                        // the pixels

                                              // build mipmaps
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, myPixmap.nCols, myPixmap.nRows, GL_RGB, GL_UNSIGNED_BYTE, myPixmap.pixel);
  //
  // ... (repeat the above for each texture to be used)
  //

  //------------------------------------------------------------------
  //  Set texture parameters
  //  (If you have only one texture, these can be set once. If you have
  //  multiple textures and the parameter settings are different for
  //  each, you should update these settings prior to drawing the new
  //  texture.)
  //
  //  These are reasonable defaults. See the OpenGL documentation for
  //  other possible values.
  //------------------------------------------------------------------

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //------------------------------------------------------------------
  // Select ONE of the following options:
  //   GL_DECAL - best for prelit textures (e.g., skybox)
  //   GL_MODULATE - best for standard surface textures
  //   ... there are a number of others for different effects
  //------------------------------------------------------------------
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  //------------------------------------------------------------------
  //  Draw a textured object
  //  We assume that all the above initializations have been performed.
  //
  //  If GL_MODULATE is used, the color should be set to the actual
  //  object color. If GL_DECAL is used, the color choice does not
  //  really matter.
  //------------------------------------------------------------------
  glEnable(GL_TEXTURE_2D);                    // enable texture mapping
 
  GLfloat color[] = {1.0, 0.0, 1.0, 1.0};     // set surface RGBA color
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
glPushMatrix();

  if (!gameover){
	//top
	glBegin(GL_QUADS);                        // draw the object
		glTexCoord2f(.75f, .25f);
		glVertex3f (200.0f,200.0f,200.0f);
		glTexCoord2f(.75f, .75f);
		glVertex3f (200.0f,-200.0f,200.0f);
		glTexCoord2f(.25f, .75f);
		glVertex3f (-200.0f,-200.0f,200.0f);
		glTexCoord2f(.25f, .25f);
		glVertex3f (-200.0f,200.0f,200.0f);	
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.25f, .75f);
		glVertex3f (-200.0f,-200.0f,200.0f);
		glTexCoord2f(0.0f, .75f);
		glVertex3f (-200.0f,-200.0f,0.0f);
		glTexCoord2f(0.0f, .25f);
		glVertex3f (-200.0f,200.0f,0.0f);
		glTexCoord2f(.25f, .25f);
		glVertex3f (-200.0f,200.0f,200.0f);	
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.25f, .75f);
		glVertex3f (-200.0f,-200.0f,200.0f);
		glTexCoord2f(0.75f, 0.75f);
		glVertex3f (200.0f,-200.0f,200.0f);
		glTexCoord2f(.75f, 1.0f);
		glVertex3f (200.0f,-200.0f,0.0f);
		glTexCoord2f(.25f, 1.0f);
		glVertex3f (-200.0f,-200.0f,0.0f);	
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.75f, .75f);
		glVertex3f (200.0f,-200.0f,200.0f);
		glTexCoord2f(0.75f, 0.25f);
		glVertex3f (200.0f,200.0f,200.0f);
		glTexCoord2f(1.0f, .25f);
		glVertex3f (200.0f,200.0f,0.0f);
		glTexCoord2f(1.0f, .75f);
		glVertex3f (200.0f,-200.0f,0.0f);	
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.75f, .25f);
		glVertex3f (200.0f,200.0f,200.0f);
		glTexCoord2f(0.25f, 0.25f);
		glVertex3f (-200.0f,200.0f,200.0f);
		glTexCoord2f(0.25f, 0.0f);
		glVertex3f (-200.0f,200.0f,0.0f);
		glTexCoord2f(.75f, 0.0f);
		glVertex3f (200.0f,200.0f,0.0f);	
	glEnd();
	
	//bottom
	glBegin(GL_QUADS);                        // draw the object
		glTexCoord2f(.75f, .25f);
		glVertex3f (200.0f,200.0f,-200.0f);
		glTexCoord2f(.75f, .75f);
		glVertex3f (200.0f,-200.0f,-200.0f);
		glTexCoord2f(.25f, .75f);
		glVertex3f (-200.0f,-200.0f,-200.0f);
		glTexCoord2f(.25f, .25f);
		glVertex3f (-200.0f,200.0f,-200.0f);	
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.25f, .75f);
		glVertex3f (-200.0f,-200.0f,-200.0f);
		glTexCoord2f(0.0f, .75f);
		glVertex3f (-200.0f,-200.0f,0.0f);
		glTexCoord2f(0.0f, .25f);
		glVertex3f (-200.0f,200.0f,0.0f);
		glTexCoord2f(.25f, .25f);
		glVertex3f (-200.0f,200.0f,-200.0f);	
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.25f, .75f);
		glVertex3f (-200.0f,-200.0f,-200.0f);
		glTexCoord2f(0.75f, 0.75f);
		glVertex3f (200.0f,-200.0f,-200.0f);
		glTexCoord2f(.75f, 1.0f);
		glVertex3f (200.0f,-200.0f,0.0f);
		glTexCoord2f(.25f, 1.0f);
		glVertex3f (-200.0f,-200.0f,0.0f);	
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.75f, .75f);
		glVertex3f (200.0f,-200.0f,-200.0f);
		glTexCoord2f(0.75f, 0.25f);
		glVertex3f (200.0f,200.0f,-200.0f);
		glTexCoord2f(1.0f, .25f);
		glVertex3f (200.0f,200.0f,0.0f);
		glTexCoord2f(1.0f, .75f);
		glVertex3f (200.0f,-200.0f,0.0f);	
	glEnd();
	glBegin(GL_QUADS);
		glTexCoord2f(0.75f, .25f);
		glVertex3f (200.0f,200.0f,-200.0f);
		glTexCoord2f(0.25f, 0.25f);
		glVertex3f (-200.0f,200.0f,-200.0f);
		glTexCoord2f(0.25f, 0.0f);
		glVertex3f (-200.0f,200.0f,0.0f);
		glTexCoord2f(.75f, 0.0f);
		glVertex3f (200.0f,200.0f,0.0f);	
	glEnd();
  }
  glDisable(GL_TEXTURE_2D);                   // disable texture mapping
}




Camera::Camera(float eyeX, float eyeY, float eyeZ, float theta, float phi){
			x = eyeX;
			originX = x;
			y = eyeY;
			originY = y;
			z = eyeZ;
			originZ = z;
			axy = theta;
			az = phi;
			tempT = 0.0f;
			tempP = 0.0f;
			zoom = 40.0f;
		}
static Camera cEye(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
void myInit(float x, float y, float z){
	player = Smurf(0,0,0);
	cEye = Camera(0,-4,1, -30, 30);
	
	gameover = false;
	win = false;
	spawnCount = 0;
}

void reset(){
	player = Smurf(0,0,0);
	cEye = Camera(0,-4,1, -30, 30);
	list<Zombie>::iterator z1;
	for (z1 = zList.begin(); z1!=zList.end();){ 
		z1 = zList.erase(z1); 
	}
	gameover = false;
	win = false;
	spawnCount = 0;
}


void renderScene(void) {
	
		// Clear Color and Depth Buffers
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		// Reset transformations
		glLoadIdentity();
		// Set the camera
// 		gluLookAt( x, 1.0f, z,
// 				x+lx, 1.0f, z+lz,
// 				0.0f, 1.0f, 0.0f);
		
		
		cEye.setCamera();
		gluLookAt(cEye.getX(), cEye.getY(), cEye.getZ(),
				player.getX(), player.getY(), 0.0f,
 				0.0f, 0.0f, 1.0f);

		//set the light
		glClearColor(0.1, 0.1, 0.1, 1.0); // intentionally back.ground
		makeSkyBox();

		glEnable(GL_NORMALIZE); // normalize normal vectors
		glShadeModel(GL_SMOOTH); // do smooth shading
		glEnable(GL_LIGHTING); // enable lighting
		// ambient light (red)
		GLfloat ambientIntensity[4] = {0.9, 0.9, 0.9, 1.0};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientIntensity);
		// set up light 0 properties
		GLfloat lt0Intensity[4] = {.7, .7, .7, 1.0}; // white
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lt0Intensity);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lt0Intensity);
		GLfloat lt0Position[4] = {0.0, 0.0, 5.0, 0.0}; // location
		glLightfv(GL_LIGHT0, GL_POSITION, lt0Position);
		// attenuation params (a,b,c)
		glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
		glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
		glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
		glEnable(GL_LIGHT0);

		GLfloat color[] = {0.6, 0.6, 0.6, 1.0}; // gray
		GLfloat white[] = {.8, .8, .8, 1.0}; // white
		// set object colors
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
		
		// Draw ground
// 		glColor3f(0.9f, 0.9f, 0.9f);
// 		glBegin(GL_QUADS);
// 		glNormal3f(0.0f, 10.0f, 0.0f);
// 		glVertex3f(-50.0f, 0.0f, -50.0f);
// 		glNormal3f(0.0f, 10.0f, 0.0f);
// 		glVertex3f(-50.0f, 0.0f, 50.0f);
// 		glNormal3f(0.0f, 10.0f, 0.0f);
// 		glVertex3f( 50.0f, 0.0f, 50.0f);
// 		glNormal3f(0.0f, 10.0f, 0.0f);
// 		glVertex3f( .0f, 0.0f, -200.0f);
// 		glEnd();
		
		for (int t1 = -5; t1 <=5; t1++){ 
			for (int t2 = -5; t2 <= 5; t2++){
				drawTile(5.5f*t1, 5.5f*t2);
			}
		}
		
		GLfloat color2[] = {0.0, 0.4, 1.6, 1.0}; // cyan
		GLfloat color3[] = {0.4, 0.1, 0.1, 1.0}; // red
		GLfloat white2[] = {0.9, 0.9, 0.9, 1.0}; // white
		// set object colors
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white2);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
		
		//glPushMatrix();
		glTranslatef(0,0,0);
		glColor3f(0.0f, 0.9f, 1.0f);
		player.draw();
		//glCallList(snowman_display_list);
		//glPopMatrix();
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color3);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white2);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25);
		list<Zombie>::iterator z1;
		glColor3f(1.0f, 0.2f, 0.2f);
		for (z1 = zList.begin(); z1!=zList.end(); ++z1){ 
			z1->draw(); 
		}
		
		//drawShadows(0.0f, 0.0f, 5.0f);
	
	
	glutSwapBuffers();
}

void myIdle() { 
	static int clock = 0;
	double elapsedTime = 0;
	static bool first = true;
	if (first){
		clock = getMilliCount();
		first = false;
	}
	elapsedTime = getMilliSpan(clock)/1000.0;
	list<Zombie>::iterator z;
	for (z = zList.begin(); z!=zList.end(); ++z){ 
			z->checkCollision(); 
	}
	if (!gameover){
		double r = double(rand())/double(RAND_MAX); 
		player.moveZ(elapsedTime);
		player.moveXY(elapsedTime);
		list<Zombie>::iterator z1;
		if  (r < .007 && spawnCount < MAX_Z){ 
			double rangeX = 20;
			float zLocX = float(fmod(rand(),rangeX)) - 10.0f; 
			double rangeY = 20;
			float zLocY = float(fmod(rand(),rangeY)) - 10.0f; 
			double rangeA = 360;
			float zAngle = float(fmod(rand(),rangeA)); 
			Zombie z1 = Zombie(zLocX, zLocY, zAngle);
			zList.push_back(z1); // make max of 30
			spawnCount += 1;
			//printf("%d\n", spawnCount);
		}
		if (spawnCount == 30 && zList.size() == 0){
			win = true;
		}
		else{
			for (z1 = zList.begin(); z1!=zList.end();){ 
				if (z1->getZ() <= -40.0f){
					z1 = zList.erase(z1);
				}
				else {
					z1->spawnZombie(elapsedTime);
					z1->rotate(elapsedTime); 
					z1->move(elapsedTime);
					++z1;
				}
			}
		}
	}
	clock = getMilliCount();
	glutPostRedisplay();
}


void changeSize(int w, int h) {
	
	
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
	h = 1;
	float ratio = w * 1.0 / h;
	
	// Use the Projection /*Matrix*/
	glMatrixMode(GL_PROJECTION);
	
	// Reset Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	
	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 10000.0f);
	
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	
	reset();
}

void makeWin(){
	spawnCount = 30;
	list<Zombie>::iterator z1;
	for (z1 = zList.begin(); z1!=zList.end();){ 
			z1 = zList.erase(z1);
	}
	win = true;
}

void processNormalKeys(unsigned char key, int x, int y) {
	//get vectors and distance between smurf and camera
	float vx = player.getX() - cEye.getX();
	float vy = player.getY() - cEye.getY();
	//float vz = player.getZ() - cEye.getZ();
	float l = sqrt(vx*vx + vy*vy);
	//normalize
	vx /= l;
	vy /= l;
	switch (key){                                // c is the key that is hit
        case 'q':                               // 'q' means quit
            exit(0);
            break;
	case 'w':
		player.hasMoved(vx, vy);
		break;
	case 'd':
		player.hasMoved(vy,-1*vx);
		break;
	case 'a':
		player.hasMoved(-1*vy,vx);
		break;
	case 's':
		player.hasMoved(-1*vx,-1*vy);
		break;
	case 'i':
		cEye.zoomIn();
		break;
	case 'o':
		cEye.zoomOut();
		break;
	case 'r':
		reset();
		break;
	case 'p':  //for auto win
		makeWin();
		break;
	default:
		break;
	}
}

void processSpecialKeys(int key, int xx, int yy) {

//float fraction = 0.1f;

// 	switch (key) {
// 	case GLUT_KEY_LEFT :
// // 	angle += 0.1f;
// // 	lx = cos(angle);
// // 	ly = sin(angle);
// 	cEye.minusAngle();
// 	break;
// 	case GLUT_KEY_RIGHT :
// // 	angle -= 0.1f;
// // 	lx = cos(angle);
// // 	ly = sin(angle);
// 	cEye.plusAngle();
// 	break;
// 	case GLUT_KEY_UP :
// // 	x += lx * fraction;
// // 	y += ly * fraction;
// 	cEye.plusAnglePhi();
// 	break;
// 	case GLUT_KEY_DOWN :
// // 	x -= lx * fraction;
// // 	y -= ly * fraction;
// 	cEye.minusAnglePhi();
// 	break;
// 	}
}

float tempMX = 0.0f;
float tempMY = 0.0f;
bool mouseDown = false;

void myMotion(int x, int y){
  //if (x != mouseX || y != mouseY){
    mouseX = x;
    mouseY = y;
	//printf("click1");
	if (mouseDown == true && !(player.tfFall())){
		cEye.changeAngleT(mouseX-tempMX);
		cEye.changeAnglePhi(mouseY-tempMY);
	}
    
}

void myMouse(int b, int s, int x, int y) {      // mouse click callback
	switch(b){
		case GLUT_LEFT_BUTTON:
			if (s == GLUT_DOWN){
				// save angle
				tempMX = x;
				tempMY = y;
				cEye.saveAngles();
				mouseDown = true;
				break;
			}
			else if (s == GLUT_UP){
				mouseDown = false;
				//break;
			}
		case GLUT_RIGHT_BUTTON:
			if (s == GLUT_DOWN){
				player.hasJumped();
				break;
			}
			
		default:
			break;
	}
}



int main(int argc, char **argv) {
//to hide console
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
// init GLUT and create window

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(800, 600);
glutCreateWindow("Smurfs VS Zombies");

myInit(0,0,0);
// register callbacks
glutIdleFunc(myIdle); 
glutDisplayFunc(renderScene);
glutReshapeFunc(changeSize);
glutKeyboardFunc(processNormalKeys);
glutMotionFunc(myMotion);
glutMouseFunc(myMouse);
glutSpecialFunc(processSpecialKeys);


// OpenGL init
glEnable(GL_DEPTH_TEST);

// enter GLUT event processing cycle
glutMainLoop();
  return 0;                                   // ANSI C expects this
}
