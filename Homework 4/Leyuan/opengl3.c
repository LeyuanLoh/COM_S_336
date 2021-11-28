#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define W 600
#define H 400

double perspective(double val, double z)
{
  return val / (1 - z);
}

void render(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINES);
  glVertex2f(-.5, -.5);
  glVertex2f(.5, -.5);
  glVertex2f(-.5, -.25);
  glVertex2f(.5, -.25);
  glVertex2f(-.5, .0);
  glVertex2f(.5, .0);
  glVertex2f(-.5, .25);
  glVertex2f(.5, .25);
  glVertex2f(-.5, .5);
  glVertex2f(.5, .5);

  glVertex2f(-.5, -.5);
  glVertex2f(-.5, .5);
  glVertex2f(-.25, -.5);
  glVertex2f(-.25, .5);
  glVertex2f(.0, -.5);
  glVertex2f(.0, .5);
  glVertex2f(.25, -.5);
  glVertex2f(.25, .5);
  glVertex2f(.5, -.5);
  glVertex2f(.5, .5);

  glEnd();
  glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  static double f = 1.0;
  int do_F = 1;

  switch (key) {
  case 'l':
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-.5, -.5);
    glVertex2f(.5, -.5);
    glVertex2f(-.5, -.25);
    glVertex2f(.5, -.25);
    glVertex2f(-.5, .0);
    glVertex2f(.5, .0);
    glVertex2f(-.5, .25);
    glVertex2f(.5, .25);
    glVertex2f(-.5, .5);
    glVertex2f(.5, .5);

    glVertex2f(-.5, -.5);
    glVertex2f(-.5, .5);
    glVertex2f(-.25, -.5);
    glVertex2f(-.25, .5);
    glVertex2f(.0, -.5);
    glVertex2f(.0, .5);
    glVertex2f(.25, -.5);
    glVertex2f(.25, .5);
    glVertex2f(.5, -.5);
    glVertex2f(.5, .5);
    
    glEnd();
    glFlush();
  break;
  case 'f':
    f /= 1.01;
    do_F = 0;
  case 'F':
    if (do_F) {
      f *= 1.01;
    }
  case 'L':
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(perspective(-.5, 0 * f), perspective(-.5, 0 * f));
    glVertex2f(perspective(.5, 0 * f), perspective(-.5, 0 * f));
    glVertex2f(perspective(-.5, -.25 * f), perspective(-.25, -.25 * f));
    glVertex2f(perspective(.5, -.25 * f), perspective(-.25, -.25 * f));
    glVertex2f(perspective(-.5, -.5 * f), perspective(.0, -.5 * f));
    glVertex2f(perspective(.5, -.5 * f), perspective(.0, -.5 * f));
    glVertex2f(perspective(-.5, -.75 * f), perspective(.25, -.75 * f));
    glVertex2f(perspective(.5, -.75 * f), perspective(.25, -.75 * f));
    glVertex2f(perspective(-.5, -1 * f), perspective(.5, -1 * f));
    glVertex2f(perspective(.5, -1 * f), perspective(.5, -1 * f));

    glVertex2f(perspective(-.5, 0 * f), perspective(-.5, 0 * f));
    glVertex2f(perspective(-.5, -1 * f), perspective(.5, -1 * f));
    glVertex2f(perspective(-.25, 0 * f), perspective(-.5, 0 * f));
    glVertex2f(perspective(-.25, -1 * f), perspective(.5, -1 * f));
    glVertex2f(perspective(.0, 0 * f), perspective(-.5, 0 * f));
    glVertex2f(perspective(.0, -1 * f), perspective(.5, -1 * f));
    glVertex2f(perspective(.25, 0 * f), perspective(-.5, 0 * f));
    glVertex2f(perspective(.25, -1 * f), perspective(.5, -1 * f));
    glVertex2f(perspective(.5, 0 * f), perspective(-.5, 0 * f));
    glVertex2f(perspective(.5, -1 * f), perspective(.5, -1 * f));

    glEnd();
    glFlush();
  break;
  case 'q':
  case 'Q':
    exit(0);
    break;
  default:
    printf("Read '%c' with mouse at (%d,%d)\n", key, x, y);
  }
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(W, W);
  glutCreateWindow("Projection Demo/Experiment");
  glutKeyboardFunc(keyboard);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glutDisplayFunc(render);
  glutMainLoop();

  return 0;
}

