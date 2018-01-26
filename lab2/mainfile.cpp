#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;

const string QUIZ = "1";

const int WIN_LEFT = 60;
const int WIN_RIGHT = 740;
const int WIN_BOTTOM = 55;
const int WIN_TOP = 600;

const int WIN_WIDTH = WIN_RIGHT - WIN_LEFT;
const int WIN_HEIGHT = WIN_TOP - WIN_BOTTOM;
const int VIEW_WIDTH = WIN_WIDTH / 5;
const int VIEW_HEIGHT = WIN_HEIGHT / 5;

const int FUNC_X_STEPS = 100;

void draw_polygon_from_input(ifstream &fi, bool flip) {
    int n; fi >> n;

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < n; ++i) {
        double x, y;
        fi >> x >> y;
        if (flip) y = WIN_TOP + WIN_BOTTOM - y;
        glVertex2d(x, y);
    }
    glEnd();
}

void draw_dinosaur(bool flip) {
    ifstream fi("../lab2/dinosaur.dat");
    int n; fi >> n;
    for (int k = 0; k < n; ++k) draw_polygon_from_input(fi, flip);
    fi.close();
}

void draw_function(const function<double(double)> &f) {
    // Get proper size
    double y_abs_max = -INFINITY;
    for (int i = 0; i <= FUNC_X_STEPS; ++i) {
        double x = 20.0 / FUNC_X_STEPS * i - 10;
        double y = f(x);
        y_abs_max = max(y_abs_max, abs(y));
    }

    gluOrtho2D(-10, 10, -y_abs_max, y_abs_max);

    // Oxy
    glBegin(GL_LINES);
    glColor3d(0, 0, 0);
    glVertex2d(-10, 0);
    glVertex2d(10, 0);
    glVertex2d(0, -y_abs_max);
    glVertex2d(0, y_abs_max);
    glEnd();

    // Function
    glBegin(GL_LINE_STRIP);
    glColor3d(0, 0, 1);
    for (int i = 0; i <= FUNC_X_STEPS; ++i) {
        double x = 20.0 / FUNC_X_STEPS * i - 10;
        double y = f(x);
        glVertex2d(x, y);
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
    // Clear
    glClear( GL_COLOR_BUFFER_BIT );

    // 1
    if (QUIZ == "1") {
        gluOrtho2D(WIN_LEFT, WIN_RIGHT, WIN_BOTTOM, WIN_TOP);
        glColor3d(0, 0, 0);
        draw_dinosaur(false);
    }

    // 2
    if (QUIZ[0] == '2') {
        gluOrtho2D(WIN_LEFT, WIN_RIGHT, WIN_BOTTOM, WIN_TOP);
        glColor3d(0, 0, 0);

        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j) {
                int x = i * VIEW_WIDTH;
                int y = j * VIEW_HEIGHT;
                glViewport(x, y, VIEW_WIDTH, VIEW_HEIGHT);

                bool flip = (QUIZ[1] == 'A' ? false : (i - j) % 2 == 0);
                draw_dinosaur(flip);
            }
    }

    // 3A
    if (QUIZ == "3A") {
        auto f = [](double x) { return pow(x, 3) + 2 * pow(x, 2) + 3; };
        draw_function(f);
    }

    // 3B
    if (QUIZ == "3B") {
        auto f = [](double x) { return 2 * sin(x) + 0.5 * cos(x); };
        draw_function(f);
    }

    // Flush
    glFlush();
}

int main( int argc, char *argv[] )  {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize( WIN_WIDTH, WIN_HEIGHT );
    glutCreateWindow( "Lab2" );
    myInit( );
    glutDisplayFunc( myDisplay );
    glutMainLoop( );
}