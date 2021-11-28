#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"

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

  matrix M, Mvp, Morth, Mper, tmp;
  vector in, out;

  int i;

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
    break;
  case 'v':
  case 'V':
    m_viewport(Mvp, 600, 600);
    printf("Mvp:\n");
    m_print(Mvp);

    in[0] = .5;
    in[1] = -.5;
    in[2] = -.25;
    in[3] = 1;
    mv_mul(out, Mvp, in);
    printf("Transforming ");
    v_print(in);
    v_print(out);

    m_orth(Morth, 1, -1, 1, -1, 1, -1);
    printf("Morth:\n");
    m_print(Morth);

    printf("Mvp*Morth:\n");
    mm_mul(M, Mvp, Morth);
    m_print(M);

    in[0] = .5;
    in[1] = -.5;
    in[2] = -.25;
    in[3] = 1;
    mv_mul(out, M, in);
    printf("Transforming ");
    v_print(in);
    v_print(out);

    m_per(Mper, 1, -1);
    printf("Mper:\n");
    m_print(Mper);

    m_copy(tmp, M);
    mm_mul(M, tmp, Mper);
    printf("Mvp*Morth*Mper:\n");
    m_print(M);

    in[0] = .5;
    in[1] = -.5;
    in[2] = -.25;
    in[3] = 1;
    mv_mul(out, M, in);
    printf("Transforming ");
    v_print(in);
    v_print(out);
    printf("Normalizing ");
    v_normalize(out);
    v_print(out);

    in[0] = .5;
    in[1] = -.5;
    in[2] = -.5;
    in[3] = 1;
    mv_mul(out, M, in);
    printf("Transforming ");
    v_print(in);
    v_print(out);
    printf("Normalizing ");
    v_normalize(out);
    v_print(out);

    printf("Normalized points on a line moving through z:");
    in[0] = .5;
    in[1] = .5;
    in[2] = .5;
    in[3] = 1;
    for (i = 0; i < 100000; i++) {
      printf("In: ");
      v_print(in);
      mv_mul(out, M, in);
      v_normalize(out);
      printf("                                        Out: ");
      v_print(out);
      in[2] += .1;
    }
    printf("Done\n");

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
  glutCreateWindow("OpenGL Matrix Demo");
  glutKeyboardFunc(keyboard);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-W/2, W/2, -W/2, W/2, 1, -1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glutDisplayFunc(hello);
  glutMainLoop();

  return 0;
}

