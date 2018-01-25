#include <gl/gl.h>
#include <gl/glut.h>

void myInit()  {
    glClearColor(1, 1, 1, 0);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glEnable(GL_LINE_SMOOTH);
    gluOrtho2D(0, 640, 0, 480);
}

void myDisplay()  {
    // Clear
    glClear( GL_COLOR_BUFFER_BIT );

    // Draw

    // Flush
    glFlush();
}

int main( int argc, char *argv[] )  {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "Lab4" );
    myInit( );
    glutDisplayFunc( myDisplay );
    glutMainLoop( );
}