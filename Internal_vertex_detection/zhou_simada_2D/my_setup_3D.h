
/***********************************************************


   This header file contains initialization function calls and set-ups
for basic 3D CS 445/545 Open GL (Mesa) programs that use the GLUT.
The initializations involve defining a callback handler (my_reshape_function)
that sets viewing parameters for orthographic 3D display.

   TSN 02/2010, updated 01/2012

 ************************************************************/

#include<math.h>
/* reshape callback handler - defines viewing parameters */
#define PI 3.14159265

void my_3d_projection(int width, int height)
    {
    GLfloat width_bound, height_bound;
    width_bound = width; height_bound = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400,400,-400,400,0,1000);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);
    glClearColor(0.0,0.0,0.0,0.0);
    }

#define STRT_X_POS 25
#define STRT_Y_POS 25

void my_setup(int width, int height, char *window_name_str)
    {
    // To get double buffering, uncomment the following line
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    // below code line does single buffering - if above line is uncommented,
    // the single buffering line will have to be commented out
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  
    glutInitWindowSize(width, height);
    glutInitWindowPosition(STRT_X_POS,STRT_Y_POS);
    glutCreateWindow(window_name_str);
    glutReshapeFunc(my_3d_projection);
    }

