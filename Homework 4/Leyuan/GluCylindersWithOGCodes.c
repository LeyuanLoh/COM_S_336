/*
 * GluCylinders.c   - Version 1.0.
 *
 * Author: Samuel R. Buss, Leyuan Loh, Duong Hoang Vu
 *
 * Bug reports: Sam Buss, sbuss@ucsd.edu.
 * 
 * PURPOSE: Provide routines for drawing cylinders with gluQuadricObjects
 *     Since GLUT does not support cylinders, this adds useful support
 *		for these common shapes.
 *
 * USAGE:   
 *    Press arrow keys to control view position.
 *			left and right keys rotate the viewpoint left and right
 *	  Up and down keys rotate viewpoint up and down (up to 80 degrees).
 *
 *    Press "R" key to make step size bigger (if moving too slowly)
 *    Press "r" key to make step size smaller (if moving too fast).
 *	 
 *    Press the "w" key to toggle wireframe mode (looks terrible in "fill" mode)
 *  
 *	  Press ESCAPE to exit.
 *
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

// ************************************************************************
// These are four general purpose routines for generating
//	cylinders, with or without caps.
// See the OpenGL redbook or other glu documentation for more information.
// These generate normals, but not texture coordinates.
// To generate texture coordinates, you need to modify the code to
//   call gluQuadricTexture();
// For higher performance, you should consider putting your cylinders into
//	 a display list.
// Please note these routines do not do all possible error checking, and
//	 thus should not be used in a production or other critical environment.
// ************************************************************************

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

void rotateJoint(int jointIndex, int key)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		jointRotation[jointIndex][0] -= AngleStepSize;
		if (jointRotation[jointIndex][0] < -50.0f)
		{
			jointRotation[jointIndex][0] = -50.0f;
		}
		break;
	case GLUT_KEY_UP:
		jointRotation[jointIndex][0] += AngleStepSize;
		if (jointRotation[jointIndex][0] > 50.0f)
		{
			jointRotation[jointIndex][0] = 50.0f;
		}
		break;
	case GLUT_KEY_RIGHT:
		jointRotation[jointIndex][1] += AngleStepSize;
		if (jointRotation[jointIndex][1] > 50.0f)
		{
			jointRotation[jointIndex][1] = 50.0f;
		}
		break;
	case GLUT_KEY_LEFT:
		jointRotation[jointIndex][1] -= AngleStepSize;
		if (jointRotation[jointIndex][1] < -50.0f)
		{
			jointRotation[jointIndex][1] = -50.0f;
		}
		break;
	}
	glutPostRedisplay();
}

// glutKeyboardFunc is called below to set this function to handle
//		all "normal" key presses.
void myKeyboardFunc(unsigned char key, int x, int y)
{
	
	// printf("Rotate Mode\n");
	switch (key)
	{
	// case 'z':
	// 	//Switching to rotating joint A mode
	// 	if (jointSelection[jointAIndex])
	// 	{
	// 		jointSelection[jointAIndex] = false;
	// 		break;
	// 	}
	// 	jointSelection[jointAIndex] = true;
	// 	break;

	// case 'x':
	// 	//Switching to rotating joint B mode
	// 	if (jointSelection[jointBIndex])
	// 	{
	// 		jointSelection[jointBIndex] = false;
	// 		break;
	// 	}
	// 	jointSelection[jointBIndex] = true;
	// 	break;

	// case 'c':
	// 	//Switching to rotating joint C mode
	// 	if (jointSelection[jointCIndex])
	// 	{
	// 		jointSelection[jointCIndex] = false;
	// 		break;
	// 	}
	// 	jointSelection[jointCIndex] = true;
	// 	break;

	// case 'v':
	// 	//Switching to rotating joint C mode
	// 	if (jointSelection[jointDIndex])
	// 	{
	// 		jointSelection[jointDIndex] = false;
	// 		break;
	// 	}
	// 	jointSelection[jointDIndex] = true;
	// 	break;
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
		jointRotation[1][2] += AngleStepSize;
		break;
	case 'U':
		jointRotation[1][2] -= AngleStepSize;	
		break;
	case 'v':
		jointRotation[1][0] += AngleStepSize;
		break;
	case 'V':
		jointRotation[1][0] -= AngleStepSize;
		break;
	case 'w':
		jointRotation[1][1] += AngleStepSize;
		break;	
	case 'W':
		jointRotation[1][1] -= AngleStepSize;
		break;
	case 'c':
		break;
	case 'C':
		break;
	case 'r':
		break;
	case 'R':
		break;
	case 'p':
		break;
	case 'P':
		break;
	case 'a':
		break;
	case 'A':
		break;
	case 'o':
		break;
	// case 'w':
	// 	WireFrameOn = 1 - WireFrameOn;
	// 	if (WireFrameOn)
	// 	{
	// 		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Just show wireframes
	// 	}
	// 	else
	// 	{
	// 		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Show solid polygons
	// 	}
	// 	glutPostRedisplay();
	// 	break;
	// case 'R':
	// 	AngleStepSize *= 1.5;
	// 	if (AngleStepSize > AngleStepMax)
	// 	{
	// 		AngleStepSize = AngleStepMax;
	// 	}
	// 	break;
	// case 'r':
	// 	AngleStepSize /= 1.5;
	// 	if (AngleStepSize < AngleStepMin)
	// 	{
	// 		AngleStepSize = AngleStepMin;
	// 	}
	// 	break;
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
	glRotatef(90, 1.0, 0.0, 0.0);

	//If disabled, then you can see the color from both sides
	glDisable(GL_CULL_FACE);
	//The first push load in the current matrix for the relative position of the arm entity
	// glPushMatrix();
	glTranslatef(0, 0.0, 0.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(270, 0.0, 1.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.2, 1.0, 0.2); // Greenish color
	// Parameters: height, base radius, top radius, slices, stacks
	drawArmJoint(JOINTAHEIGHT, JOINTBASERADIUS, 32, 32);
	//Popping replacing the current matrix with the one below it, essentially wiping out position data of the first joint
	// glPopMatrix();

	//If disabled, then you can see the color from both sides, or in and out
	glDisable(GL_CULL_FACE);
	//Dont need to push cause we are reusing the previous joint position
	// glPushMatrix();
	glTranslatef(0, 0.0, JOINTAHEIGHT);
	glRotatef(jointRotation[jointBIndex][2], 1.0, 0.0, 0.0);
	glRotatef(jointRotation[jointBIndex][1], 0.0, 1.0, 0.0);
	glRotatef(jointRotation[jointBIndex][0], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.2, 0.2); // Reddish color
	// Parameters: height, radius, slices, stacks
	drawArmJoint(JOINTBHEIGHT, JOINTBASERADIUS, 32, 32);

	//This function duplicating the current matrix of the object on the stack to the object below
	//Popping replacing the current matrix with the one below it, essentially wiping out position data of the first joint
	// glPopMatrix();

	//If disabled, then you can see the color from both sides, or in and out
	glDisable(GL_CULL_FACE);
	//Dont need to push cause we are reusing the previous joint position
	// glPushMatrix();
	glTranslatef(0, 0.0, JOINTBHEIGHT);
	glRotatef(jointRotation[jointCIndex][2], 1.0, 0.0, 0.0);
	glRotatef(jointRotation[jointCIndex][1], 0.0, 1.0, 0.0);
	glRotatef(jointRotation[jointCIndex][0], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.0); // Orange color
	// Parameters: height, radius, slices, stacks
	drawArmJoint(JOINTCHEIGHT, JOINTBASERADIUS, 32, 32);

	//This function duplicating the current matrix of the object on the stack to the object below
	//Popping replacing the current matrix with the one below it, essentially wiping out position data of the first joint
	// glPopMatrix();



	//If disabled, then you can see the color from both sides, or in and out
	glDisable(GL_CULL_FACE);
	//Dont need to push cause we are reusing the previous joint position
	// glPushMatrix();
	glTranslatef(0, 0.0, JOINTCHEIGHT);
	glRotatef(jointRotation[jointDIndex][2], 1.0, 0.0, 0.0);
	glRotatef(jointRotation[jointDIndex][1], 0.0, 1.0, 0.0);
	glRotatef(jointRotation[jointDIndex][0], 0.0, 0.0, 1.0);
	glColor3f(0.5, 0, 0.5); // Purple color
	// Parameters: height, radius, slices, stacks
	drawArmJoint(JOINTDHEIGHT, JOINTBASERADIUS, 32, 32);

	//This function duplicating the current matrix of the object on the stack to the object below
	//Popping replacing the current matrix with the one below it, essentially wiping out position data of the first joint
	// glPopMatrix();


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

	// Define the portion of the window used for OpenGL rendering.
	glViewport(0, 0, w, h); // View port uses whole window

	// Set up the projection view matrix: perspective projection
	// Determine the min and max values for x and y that should appear in the window.
	// The complication is that the aspect ratio of the window may not match the
	//		aspect ratio of the scene we want to view.
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;
	aspectRatio = (double)w / (double)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Aspect ratio + view distance (depth - last paramter)
	gluPerspective(15.0, aspectRatio, 25.0, 100.0);
}

// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	// We're going to animate it, so double buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Window position (from top corner), and size (width% and hieght)
	glutInitWindowPosition(10, 60);
	glutInitWindowSize(900, 900);
	glutCreateWindow("GluCylinders");

	// Initialize OpenGL as we like it..
	initRendering();

	// Set up callback functions for key presses
	glutKeyboardFunc(myKeyboardFunc);  // Handles "normal" ascii symbols

	// Set up the callback function for resizing windows
	glutReshapeFunc(resizeWindow);

	// Call this for background processing
	// glutIdleFunc( myIdleFunction );

	// call this whenever window needs redrawing
	glutDisplayFunc(drawScene);

	fprintf(stdout, "Arrow keys control viewpoint.\n");
	fprintf(stdout, "Press \"w\" to toggle wireframe mode.\n");
	fprintf(stdout, "Press \"R\" or \"r\" to increase or decrease rate of movement (respectively).\n");
	fprintf(stdout, "Press \"z\" to toggle joint rotation mode for joint A (green)\n");
	fprintf(stdout, "Press \"x\" to toggle joint rotation mode for joint B (orange)\n");
	fprintf(stdout, "Press \"c\" to toggle joint rotation mode for joint C (yellow)\n");
	fprintf(stdout, "Press \"v\" to toggle joint rotation mode for joint C (purple)\n");

	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop();

	return (0); // This line is never reached.
}


