/**
 * @Author Leyuan Loh and Duong Vu
 * An OpenGL program that simulates arm and hand movements. 
 * Sources: 
 * Cylinder
 * https://www.math.ucsd.edu/~sbuss/MathCG/OpenGLsoft/GluCylinders/GluCylinders.html
 * https://gist.github.com/nikAizuddin/5ea402e9073f1ef76ba6
 * Installing OpenGL
 * https://www.prinmath.com/csci5229/misc/install.html
 **/
#include <GL/gl.h>
#include <GL/glut.h>

#define W 600
#define H 400

void hello(void){
    glBegin(GL_POLYGON);

    glVertex2f (-.2,  -.3);
    glVertex2f(.3,  -.3);
    glVertex2f(.3, .3);
    glVertex2f( -.3, .3);
    
    glEnd();  
    glFlush();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  //Not sure what is the difference between without and with GLUT_RGB
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(W, H);
  glClear(GL_COLOR_BUFFER_BIT);
  glutCreateWindow("OpenGL Arm");
  glutDisplayFunc(hello);
  glutMainLoop();

  return 0;
}
