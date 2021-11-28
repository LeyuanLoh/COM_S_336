#include <GL/gl.h>
#include <GL/glut.h>

#define W 600
#define H 400

void hello(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_POLYGON);

  glVertex2f (-.3,  -.3);
  glVertex2f(.3,  -.3);
  glVertex2f(.3, .3);
  glVertex2f( -.3, .3);
  

  glEnd();

  glFlush();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(W, H);
  glutCreateWindow("OpenGL Hello World");
  glutDisplayFunc(hello);
  glutMainLoop();

  return 0;
}

