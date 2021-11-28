#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define W 600
#define H 400

double mul = 1.0;

void rotate(double deg, double *x, double *y)
{
  double rad = deg * M_PI / 180;
  double x1, y1;

  x1 = (*x) * cos(rad) - (*y) * sin(rad);
  y1 = (*x) * sin(rad) + (*y) * cos(rad);

  *x = x1;
  *y = y1;
}

void hello(void)
{
  float theta;

  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_TRIANGLES);

  for (theta = 0; theta < 2 * M_PI; theta += (M_PI / 60)) {
    glColor3f(1,0,0);
    glVertex2f((H * cos(theta)) / 2.1 + (0 * mul),
               ((H * sin(theta)) / 2.1) - (5 * mul));
    glColor3f(0,1,0);
    glVertex2f((H * cos(theta)) / 2.1 - (5 * mul),
               ((H * sin(theta)) / 2.1) + (5 * mul));
    glColor3f(0,0,1);
    glVertex2f((H * cos(theta)) / 2.1 + (5 * mul),
               ((H * sin(theta)) / 2.1) + (5 * mul));
  }

  glEnd();

  glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  static double r = 0.0;

  double xsize, ysize;

  switch (key) {
  case 'c':
  case 'C':
    hello();
    break;
  case 'q':
  case 'Q':
    exit(0);
    break;
  case 'm':
    mul /= 2.0;
    break;
  case 'M':
    mul *= 2;
    break;
  case 't':
  case 'T':
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);

    xsize = 0 * mul;
    ysize = -5 * mul;
    rotate(r, &xsize, &ysize);
    glColor3f(1,0,0);
    glVertex2f(x + xsize - W / 2,
               y + ysize - H / 2);
    xsize = -5 * mul;
    ysize = +5 * mul;
    rotate(r, &xsize, &ysize);
    glColor3f(0,1,0);
    glVertex2f(x + xsize - W / 2,
               y + ysize - H / 2);
    xsize = +5 * mul;
    ysize = +5 * mul;
    rotate(r, &xsize, &ysize);
    glColor3f(0,0,1);
    glVertex2f(x + xsize - W / 2,
               y + ysize - H / 2);

    glEnd();

    glFlush();

    r += 1.0;
  default:
    printf("Read '%c' with mouse at (%d,%d)\n", key, x, y);
  }
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(W, H);
  glutCreateWindow("OpenGL Hello World");
  glutKeyboardFunc(keyboard);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-W/2, W/2, -H/2, H/2, 1, -1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glutDisplayFunc(hello);
  glutMainLoop();

  return 0;
}

