#include <gl/gl.h>
#include <gl/glut.h>
#include <vector>
using std::vector;

void draw(GLenum e, vector<double> cords, double red, double green, double blue) {
    glBegin(e);
    glColor3d(red, green, blue);
    for (int i = 0; i < cords.size(); i += 2) {
        glVertex2d(cords[i], cords[i + 1]);
    }
    glEnd();
}

void myInit()  {
    glClearColor(1, 1, 1, 0);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glEnable(GL_LINE_SMOOTH);
}

void myDisplay()  {
    glClear( GL_COLOR_BUFFER_BIT );

    // Draw 3 points
    glPointSize(5);
    draw(GL_POINTS, vector<double>{0, 0, .5, 0, 0, .5}, 0, 0, 0);

    // Draw house
    draw(GL_QUADS, vector<double>{-.5, -1, 0, -1, 0, -.5, -.5, -.5}, 1, 0, 0);
    draw(GL_TRIANGLES, vector<double>{-.6, -.5, -.25, -.25, .1, -.5}, 0, 0, 1);

    // Flush
    glFlush();
}

int main( int argc, char *argv[] )  {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "Lab1" );
    myInit( );
    glutDisplayFunc( myDisplay );
    glutMainLoop( );
}