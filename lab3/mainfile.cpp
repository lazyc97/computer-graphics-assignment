#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <string>
#include <vector>
#include <functional>

using namespace std;

const string QUIZ = "1";
const double PI = acos(-1);

struct point {
    GLdouble x, y;
    point(GLdouble x, GLdouble y): x(x), y(y) {}
};

void drawSnowFlake(int gen) {
    vector<point> cur_gen, next_gen;
    cur_gen.emplace_back(-0.5, 0.5);
    cur_gen.emplace_back(0, 0.5 - sqrt(3) / 2);
    cur_gen.emplace_back(0.5, 0.5);
    cur_gen.emplace_back(-0.5, 0.5);

    for (int i = 1; i < gen; ++i) {
        next_gen.push_back(cur_gen.front());
        for (int j = 1; j < cur_gen.size(); ++j) {
            auto &a = cur_gen[j - 1];
            auto &b = cur_gen[j];

            auto mx = (a.x + b.x) / 2;
            auto my = (a.y + b.y) / 2;
            auto dx = b.x - a.x;
            auto dy = b.y - a.y;
            auto hx = dy / 3 * sqrt(3) / 2;
            auto hy = -dx / 3 * sqrt(3) / 2;

            next_gen.emplace_back(a.x + dx / 3, a.y + dy / 3);
            next_gen.emplace_back(mx + hx, my + hy);
            next_gen.emplace_back(a.x + dx * 2 / 3, a.y + dy * 2 / 3);

            next_gen.push_back(b);
        }

        cur_gen.swap(next_gen);
        next_gen.clear();
    }

    glBegin(GL_LINE_STRIP);
    for (auto p : cur_gen) glVertex2d(p.x, p.y);
    glEnd();
}

template <typename FX, typename FY>
void draw_function(FX fx, FY fy, double lt, double rt) {
    auto dt = (rt - lt) / 1000;
    glBegin(GL_LINE_STRIP);

    for (auto t = lt; t <= rt; t += dt) {
        double x = fx(t);
        double y = fy(t);
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
    glColor3d(0, 0, 0);

    // Snow flake
    if (QUIZ == "1") drawSnowFlake(5);

    // Function
    if (QUIZ[0] == '2') {
        // Cardioid
        if (QUIZ[1] == 'A') {
            double a = 0.1;
            auto fx = [a](double t) { return 2 * a * (1 - cos(t)) * cos(t); };
            auto fy = [a](double t) { return 2 * a * (1 - cos(t)) * sin(t); };
            draw_function(fx, fy, 0, 2 * PI);
        }

        // Rose
        if (QUIZ[1] == 'B') {
            double a = 1;
            double k = 3;

            double dx = -0.1;
            double dy = 0;
            auto fx = [a, k, dx](double t) { return a * cos(k * t) * cos(t) + dx; };
            auto fy = [a, k, dy](double t) { return a * cos(k * t) * sin(t) + dy; };
            draw_function(fx, fy, 0, 2 * PI);
        }

        // Archimedean spiral
        if (QUIZ[1] == 'C') {
            double a = 0.04;
            auto fx = [a](double t) { return a * t * cos(t); };
            auto fy = [a](double t) { return a * t * sin(t); };
            draw_function(fx, fy, 0, 10 * PI);
        }
    }

    // Flush
    glFlush();
}

int main( int argc, char *argv[] )  {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "Lab3" );
    myInit( );
    glutDisplayFunc( myDisplay );
    glutMainLoop( );
}