/*
 *
 * Author: Samuel R. Buss, Leyuan Loh, Duong Hoang Vu
 * An OpenGL program that simulates arm and hand movements. 
 * Sources: 
 * Cylinder
 * https://www.math.ucsd.edu/~sbuss/MathCG/OpenGLsoft/GluCylinders/GluCylinders.html
 * https://gist.github.com/nikAizuddin/5ea402e9073f1ef76ba6
 * Installing OpenGL
 * https://www.prinmath.com/csci5229/misc/install.html
*/

#include <math.h> // For math routines (such as sqrt & trig).
#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h> // OpenGL Graphics Utility Library
#include "GluCylinders.h"

#define JOINTBASERADIUS 1
#define JOINTAHEIGHT  4
#define JOINTBHEIGHT  4
#define JOINTCHEIGHT  3
#define JOINTDHEIGHT 2.5

#define WIDTH 900
#define HEIGHT 900

#define X 0 
#define Y 1
#define Z 2

//rotations of joins (about y first then about z, then x)
float jointRotation[4][3] = {{0, 0, 0}, {0, 270, 0}, {0, 0, 0}, {0,0,0}};
int jointAIndex = 0;
int jointBIndex = 1;
int jointCIndex = 2;
int jointDIndex = 3;

double translations[3] = {JOINTAHEIGHT,4,-80.0};


float AngleStepSize = 3.0f; // Step three degrees at a time
const float AngleStepMax = 10.0f;
const float AngleStepMin = 0.1f;

int WireFrameOn = 1; // == 1 for wire frame mode

int ortho = 1;

//  A Reusable gluQuadric object:
GLUquadricObj *myReusableQuadric = 0;

void drawGluCylinder(double height, double radius, int slices, int stacks)
{
	drawGluSlantCylinder(height, radius, radius, slices, stacks);
}

void drawGluSlantCylinder(double height, double radiusBase, double radiusTop, int slices, int stacks)
{
	if (!myReusableQuadric)
	{
		myReusableQuadric = gluNewQuadric();
		// Should (but don't) check if pointer is still null --- to catch memory allocation errors.
		gluQuadricNormals(myReusableQuadric, GL_TRUE);
	}
	// Draw the cylinder.
	gluCylinder(myReusableQuadric, radiusBase, radiusTop, height, slices, stacks);
}


void drawArmJoint(double height, double baseRadius, int slices, int stacks)
{
	drawGluCylinder(height, baseRadius, slices, stacks);

	//Draw the top disk of the joint
	glPushMatrix();
	glTranslated(0.0, 0.0, height);
	gluDisk(myReusableQuadric, 0.0, baseRadius, slices, stacks);
	glPopMatrix();

	//Draw the bottom disk of the joint
	glPushMatrix();
	glRotated(180, 1.0, 0, 0);
	gluDisk(myReusableQuadric, 0.0, baseRadius, slices, stacks);
	glPopMatrix();
}

// glutKeyboardFunc is called below to set this function to handle
//		all "normal" key presses.
void myKeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key: %c\n", key);
	
	// printf("Rotate Mode\n");
	switch (key)
	{
	case 'x':
		translations[0] -= 0.2;
		break;
	case 'X':
		translations[0] += 0.2;
		break;
	case 'y':
		translations[1] -= 0.2;
		break;
	case 'Y':
		translations[1] += 0.2;
		break;
	case 'z':
		translations[2] -= 0.2;
		break;
	case 'Z':
		translations[2] += 0.2;
		break;
	case 'u':
		jointRotation[jointBIndex][X] += AngleStepSize;
		break;
	case 'U':
		jointRotation[jointBIndex][X] -= AngleStepSize;	
		break;
	case 'v':
		jointRotation[jointBIndex][Y] += AngleStepSize;
		break;
	case 'V':
		jointRotation[jointBIndex][Y] -= AngleStepSize;
		break;
	case 'w':
		jointRotation[jointBIndex][Z] += AngleStepSize;
		break;	
	case 'W':
		jointRotation[jointBIndex][Z] -= AngleStepSize;
		break;
	case 'c':
		jointRotation[jointCIndex][X] += AngleStepSize;
		break;
	case 'C':
		jointRotation[jointCIndex][X] -= AngleStepSize;
		break;
	case 'r':
		jointRotation[jointCIndex][Z] += AngleStepSize;
		break;
	case 'R':
		jointRotation[jointCIndex][Z] -= AngleStepSize;
		break;
	case 'p':
		jointRotation[jointDIndex][X] += AngleStepSize;
		break;
	case 'P':
		jointRotation[jointDIndex][X] -= AngleStepSize;
		break;
	case 'a':
		jointRotation[jointDIndex][Y] += AngleStepSize;
		break;
	case 'A':
		jointRotation[jointDIndex][Y] -= AngleStepSize;
		break;
	case 'o':
		ortho = ortho == 0? 1:0;
		resizeWindow(WIDTH,HEIGHT);
		printf("Ortho : %d\n", ortho);
		return;
		break;
	case '1':
		WireFrameOn = 1 - WireFrameOn;
		if (WireFrameOn)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Just show wireframes
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Show solid polygons
		}
		break;
	case '2':
		AngleStepSize *= 1.5;
		if (AngleStepSize > AngleStepMax)
		{
			AngleStepSize = AngleStepMax;
		}
		break;
	case '3':
		AngleStepSize /= 1.5;
		if (AngleStepSize < AngleStepMin)
		{
			AngleStepSize = AngleStepMin;
		}
		break;
	case 27: // Escape key
		exit(1);
	}
	glutPostRedisplay();

}

/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
void drawScene(void)
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Rotate the image`
	glMatrixMode(GL_MODELVIEW); // Current matrix affects objects positions
	glLoadIdentity();			// Initialize to the identity

	//This is for the position of the objects
	glTranslatef(translations[0], translations[1], translations[2]);					 // Translate  from origin (in front of viewer)
	glRotatef(0, 1.0, 0.0, 0.0);

	//If disabled, then you can see the color from both sides
	glDisable(GL_CULL_FACE);
	//The first push load in the current matrix for the relative position of the arm entity
	glTranslatef(0, 0.0, 0.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(270, 0.0, 1.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.2, 1.0, 0.2); // Greenish color
	// Parameters: height, base radius, top radius, slices, stacks
	drawArmJoint(JOINTAHEIGHT, JOINTBASERADIUS, 32, 32);
	//Popping replacing the current matrix with the one below it, essentially wiping out position data of the first joint
	// glPopMatrix();

	glPushMatrix();
	GLUquadric *quad;
	glTranslatef(0,0,4);
	glColor3f(0.8, 1.0, 0.2);
	quad = gluNewQuadric();
	gluSphere(quad,1,100,20);
	glPopMatrix();

	//If disabled, then you can see the color from both sides, or in and out
	glDisable(GL_CULL_FACE);
	//Dont need to push cause we are reusing the previous joint position
	glTranslatef(0, 0.0, JOINTAHEIGHT);
	glRotatef(jointRotation[jointBIndex][Y], 1.0, 0.0, 0.0);
	glRotatef(jointRotation[jointBIndex][X], 0.0, 1.0, 0.0);
	glRotatef(jointRotation[jointBIndex][Z], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.2, 0.2); // Reddish color
	// Parameters: height, radius, slices, stacks
	drawArmJoint(JOINTBHEIGHT, JOINTBASERADIUS, 32, 32);

	//This function duplicating the current matrix of the object on the stack to the object below
	//Popping replacing the current matrix with the one below it, essentially wiping out position data of the first joint
	// glPopMatrix();



	//If disabled, then you can see the color from both sides, or in and out
	glDisable(GL_CULL_FACE);
	//Dont need to push cause we are reusing the previous joint position
	glTranslatef(0, 0.0, JOINTBHEIGHT);
	glRotatef(jointRotation[jointCIndex][X], 0.0, 1.0, 0.0);
	glRotatef(jointRotation[jointCIndex][Z], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.0); // Orange color
	// Parameters: height, radius, slices, stacks
	drawArmJoint(JOINTCHEIGHT, JOINTBASERADIUS, 32, 32);

	//This function duplicating the current matrix of the object on the stack to the object below
	//Popping replacing the current matrix with the one below it, essentially wiping out position data of the first joint
	// glPopMatrix();



	//If disabled, then you can see the color from both sides, or in and out
	glDisable(GL_CULL_FACE);
	//Dont need to push cause we are reusing the previous joint position
	glTranslatef(0, 0.0, JOINTCHEIGHT);
	glRotatef(jointRotation[jointDIndex][Y], 1.0, 0.0, 0.0);
	glRotatef(jointRotation[jointDIndex][X], 0.0, 1.0, 0.0);
	glColor3f(0.5, 0, 0.5); // Purple color
	// Parameters: height, radius, slices, stacks
	drawArmJoint(JOINTDHEIGHT, JOINTBASERADIUS, 32, 32);

	//This function duplicating the current matrix of the object on the stack to the object below
	//Popping replacing the current matrix with the one below it, essentially wiping out position data of the first joint


	// Flush the pipeline, swap the buffers
	glFlush();
	glutSwapBuffers();
	
}

// Initialize OpenGL's rendering modes
void initRendering()
{
	glEnable(GL_DEPTH_TEST); // Depth testing must be turned on

	glCullFace(GL_BACK);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Just show wireframes at first
}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
	double aspectRatio;

	//Aspect ratio + view distance (depth - last paramter)
	if(ortho == 0){
		glViewport(0, 0, w, h); // View port uses whole window

		w = (w == 0) ? 1 : w;
		h = (h == 0) ? 1 : h;
		aspectRatio = (double)w / (double)h;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		printf("Perspective\n");
		gluPerspective(15.0, aspectRatio, 50.0, 100.0);
	}else{
		glViewport(0, 0, w, h); // View port uses whole window
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		printf("Ortho\n");
		glOrtho(-WIDTH/80, WIDTH/80, -HEIGHT/80, HEIGHT/80, 100, -100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	
}

// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	// We're going to animate it, so double buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("GluCylinders");

	initRendering();

	glutKeyboardFunc(myKeyboardFunc);  

	glutReshapeFunc(resizeWindow);

	glutDisplayFunc(drawScene);

	glutMainLoop();

	return 0;
}


