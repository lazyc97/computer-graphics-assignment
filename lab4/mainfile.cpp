#include <gl/gl.h>
#include <gl/glut.h>
#include <vector>
#include <iostream>

using namespace std;

const int INTERVAL = 10;

struct point {
    GLdouble x, y;
    point() = default;
    point(GLdouble x, GLdouble y): x(x), y(y) {}
};

vector<point> house = {
        point(50, 70),
        point(20, 50),
        point(20, 10),
        point(40, 10),
        point(40, 30),
        point(60, 30),
        point(60, 10),
        point(80, 10),
        point(80, 50)
};

vector<point> car = {
        point(40, 50),
        point(20, 50),
        point(10, 30),
        point(10, 15),
        point(15, 10),
        point(85, 10),
        point(90, 30),
        point(70, 30),
        point(60, 50)
};

vector<point> cords;

void draw_polygon_outline(const vector<point> &P) {
    glBegin(GL_LINE_LOOP);
    for (auto p : P) glVertex2d(p.x, p.y);
    glEnd();
}

void refresh_display(int _) {
    glutTimerFunc(100, refresh_display, 0);
    glutPostRedisplay();
}

void myInit()  {
    glClearColor(1, 1, 1, 0);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glEnable(GL_LINE_SMOOTH);
    gluOrtho2D(0, 100, 0, 100);
}

int direction = 1;
int mul = INTERVAL;
void myDisplay()  {
    // Clear
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3d(0, 0, 0);

    // Draw
    GLdouble a = (GLdouble)mul / INTERVAL;
    GLdouble b = 1 - a;

    cords.resize(house.size());
    for (int i = 0; i < cords.size(); ++i) {
        cords[i].x = a * house[i].x + b * car[i].x;
        cords[i].y = a * house[i].y + b * car[i].y;
    }

    draw_polygon_outline(cords);

    // Get next mul
    mul += direction;
    if (mul > INTERVAL || mul < 0) {
        mul -= 2 * direction;
        direction *= -1;
    }

    // Flush
    glutSwapBuffers();
}

int main( int argc, char *argv[] )  {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 640, 640 );
    glutCreateWindow( "Lab4" );
    myInit( );
    glutDisplayFunc( myDisplay );
    refresh_display(0);
    glutMainLoop( );
}