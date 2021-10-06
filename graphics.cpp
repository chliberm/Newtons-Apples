#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "triangle.h"
#include <iostream>
#include <memory>
#include <vector>
#include <time.h>
using namespace std;

GLdouble width, height;
int wd;
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(14/255.0, 143/255.0, 34/255.0);
const color treeGreen1(81/255.0, 166/255.0, 28/255.0);
const color treeGreen2(53/255.0, 153/255.0, 28/255.0);
const color treeGreen3(8/255.0, 94/255.0, 13/255.0);
const color treeGreen4(36/255.0, 87/255.0, 53/255.0);
const color treeGreen5(30/255.0, 61/255.0, 40/255.0);
const color white(1, 1, 1);
const color trunkBrown(99/255.0, 52/255.0, 4/255.0);
const color basketBrown(176/255.0, 109/255.0, 26/255.0);
const color appleRed(171/255.0, 7/255.0, 7/255.0);
const color black(0, 0, 0);
const color yellow(1, 1, 0);

enum screen_mode{
    intro,
    start,
    play,
    final
};

screen_mode screen = intro;
Rect sky;
Rect grass;
vector<unique_ptr<Shape>> clouds;
vector<unique_ptr<Shape>> tree;
Triangle test;
vector<Circle> apples;
double basketRadius;
vector<unique_ptr<Shape>> basket;
int score = 0;

void initSky() {
    sky.setCenter(width/2, height/2);
    sky.setSize(width, height);
    sky.setColor(skyBlue);
}

void initGrass() {
    grass.setCenter(width/2, height - height/8);
    grass.setSize(width, height/4);
    grass.setColor(grassGreen);
}

void initClouds() {
    clouds.clear();
    dimensions cloudBottom(30, 30);
    // First cloud
    clouds.push_back(make_unique<Circle>(white, 300, 100, 19));
    clouds.push_back(make_unique<Circle>(white, 330, 100, 20));
    clouds.push_back(make_unique<Circle>(white, 320, 90, 15));
    clouds.push_back(make_unique<Rect>(white, 315, 103, cloudBottom));
    // Second cloud
    clouds.push_back(make_unique<Circle>(white, 100, 80, 18));
    clouds.push_back(make_unique<Circle>(white, 130, 80, 16));
    clouds.push_back(make_unique<Circle>(white, 120, 70, 20));
    clouds.push_back(make_unique<Rect>(white, 115, 80, cloudBottom));
    // Third cloud
    clouds.push_back(make_unique<Circle>(white, 450, 50, 20));
    clouds.push_back(make_unique<Circle>(white, 480, 50, 22));
    clouds.push_back(make_unique<Circle>(white, 470, 40, 18));
    clouds.push_back(make_unique<Rect>(white, 465, 55, cloudBottom));
    // Fourth cloud
    clouds.push_back(make_unique<Circle>(white, 540, 110, 20));
    clouds.push_back(make_unique<Circle>(white, 570, 110, 22));
    clouds.push_back(make_unique<Circle>(white, 560, 100, 18));
    clouds.push_back(make_unique<Rect>(white, 555, 115, cloudBottom));
    // Fifth cloud
    clouds.push_back(make_unique<Circle>(white, 50, 180, 20));
    clouds.push_back(make_unique<Circle>(white, 80, 180, 22));
    clouds.push_back(make_unique<Circle>(white, 70, 170, 18));
    clouds.push_back(make_unique<Rect>(white, 65, 185, cloudBottom));
}

void initTree() {
    // Tree trunk
    dimensions trunkSize(40, height/2);
    dimensions baseSize(80, 100);
    tree.push_back(make_unique<Rect>(trunkBrown, width/2, height/2, trunkSize));
    tree.push_back(make_unique<Triangle>(trunkBrown, width/2, height - height/4, baseSize));

    // Tree top
    // First layer
    tree.push_back(make_unique<Circle>(treeGreen5, width/2, height/4 + 130, 80));
    tree.push_back(make_unique<Circle>(treeGreen5, width/2 + 40, height/4 + 130, 70));
    tree.push_back(make_unique<Circle>(treeGreen5, width/2 - 40, height/4 + 130, 70));

    // Second layer
    tree.push_back(make_unique<Circle>(treeGreen4, width/2, height/4 + 80, 100));
    tree.push_back(make_unique<Circle>(treeGreen4, width/2 + 50, height/4 + 80, 90));
    tree.push_back(make_unique<Circle>(treeGreen4, width/2 - 50, height/4 + 80, 90));


    // Third layer
    tree.push_back(make_unique<Circle>(treeGreen3, width/2, height/4 + 60, 90));
    tree.push_back(make_unique<Circle>(treeGreen3, width/2 + 45, height/4 + 60, 80));
    tree.push_back(make_unique<Circle>(treeGreen3, width/2 - 45, height/4 + 60, 80));

    // Fourth layer
    tree.push_back(make_unique<Circle>(treeGreen2, width/2, height/4 + 40, 80));
    tree.push_back(make_unique<Circle>(treeGreen2, width/2 + 40, height/4 + 40, 70));
    tree.push_back(make_unique<Circle>(treeGreen2, width/2 - 40, height/4 + 40, 70));

    // Fifth layer
    tree.push_back(make_unique<Circle>(treeGreen1, width/2, height/4 + 20, 70));
    tree.push_back(make_unique<Circle>(treeGreen1, width/2 + 35, height/4 + 20, 60));
    tree.push_back(make_unique<Circle>(treeGreen1, width/2 - 35, height/4 + 20, 60));
}

void initApples() {
    //23 apples
    for (int i = 0; i < 23; ++i) {
        apples.push_back(Circle(appleRed, rand() % 230 + int(width/2 - 115), rand() % 220 + int(height/4 - 15),
                                rand() % 10 + 5));
    }
}

void initBasket() {
    basketRadius = height/16;
    dimensions base (1.5 * basketRadius, basketRadius);
    basket.push_back(make_unique<Circle>(basketBrown, width/2, height - height/8, basketRadius ));
    basket.push_back(make_unique<Rect>(grassGreen, width/2, height - height/8 - basketRadius/2, base));
}

void init() {
    width = 600;
    height = 800;
    initSky();
    initGrass();
    initClouds();
    initTree();
    initApples();
    initBasket();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
     */
    string message;
    switch (screen) {
        case intro:
            glColor3f(99/255.0, 52/255.0, 4/255.0);
            glBegin(GL_QUADS);
            glVertex2d(50, 50);
            glVertex2d(width - 50, 50);
            glVertex2d(width - 50, height - 50);
            glVertex2d(50, height - 50);
            glColor3f(77/255.0, 213/255.0, 240/255.0);
            glVertex2d(100, 100);
            glVertex2d(width - 100, 100);
            glVertex2d(width - 100, height - 100);
            glVertex2d(100, height - 100);
            glEnd();
            message = "Welcome to Newton's Apples!";
            glColor3f(30/255.0, 61/255.0, 40/255.0);
            glRasterPos2i(width / 2 - (4 * message.length()), height / 2 );
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            message = "You must try and catch all the falling apples with the basket.";
            glRasterPos2i(width / 2 - (4 * message.length()), height / 2 + 14);
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            message = "You can move the basket with the left and right arrows.";
            glRasterPos2i(width / 2 - (4 * message.length()), height / 2 + 28);
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            message = "Press the spacebar to continue.";
            glRasterPos2i(width / 2 - (4 * message.length()), height / 2 + 42);
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            break;
        case start:
            sky.draw();
            for (unique_ptr<Shape> &s : clouds) {
                s->draw();
            }
            grass.draw();
            for (unique_ptr<Shape> &b : basket) {
                b->draw();
            }
            for (unique_ptr<Shape> &t : tree) {
                t->draw();
            }
            for (Circle &a : apples) {
                a.draw();
            }
            glColor3f(0.3, 0.3, 0.3);
            glBegin(GL_QUADS);
            glVertex2d(0, 0);
            glVertex2d(width, 0);
            glVertex2d(width, height/6);
            glVertex2d(0, height/6);
            glEnd();
            message = "You can choose the level by adjusting the size of the basket!";
            glColor3f(77/255.0, 213/255.0, 240/255.0);
            glRasterPos2i(width / 2 - (4 * message.length()), height / 12);
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            message = "Press 'g' to enlarge and 's' to shrink the basket";
            glRasterPos2i(width / 2 - (4 * message.length()), height / 12 + 14);
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            message = "When you are ready to play press the spacebar";
            glRasterPos2i(width / 2 - (4 * message.length()), height / 12 + 28);
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            break;
        case play:
            sky.draw();
            for (unique_ptr<Shape> &s : clouds) {
                s->draw();
            }
            grass.draw();
            for (unique_ptr<Shape> &b : basket) {
                b->draw();
            }
            for (unique_ptr<Shape> &t : tree) {
                t->draw();
            }
            for (Circle &a : apples) {
                a.draw();
            }
            break;
        case final:
            glColor3f(99/255.0, 52/255.0, 4/255.0);
            glBegin(GL_QUADS);
            glVertex2d(50, 50);
            glVertex2d(width - 50, 50);
            glVertex2d(width - 50, height - 50);
            glVertex2d(50, height - 50);
            glColor3f(77/255.0, 213/255.0, 240/255.0);
            glVertex2d(100, 100);
            glVertex2d(width - 100, 100);
            glVertex2d(width - 100, height - 100);
            glVertex2d(100, height - 100);
            glEnd();
            message = "Game Over!";
            glColor3f(30/255.0, 61/255.0, 40/255.0);
            glRasterPos2i(width / 2 - (4 * message.length()), height / 2 );
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            message = "Your score was " + to_string(score) + " apples.";
            glRasterPos2i(width / 2 - (4 * message.length()), height / 2 + 14);
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            break;
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    dimensions base (1.5 * basketRadius, basketRadius);
    switch(screen) {
        case intro:
            if (key == 32) {
                screen = start;
            }
            break;
        case start:
            switch (key) {
                case 'g':
                    basketRadius += 1;
                    basket[0] = make_unique<Circle>(basketBrown, width/2, height - height/8, basketRadius);
                    basket[1] = make_unique<Rect>(grassGreen, width/2, height - height/8 - basketRadius/2, base);
                    break;
                case 's':
                    basketRadius -= 1;
                    basket[0] = make_unique<Circle>(basketBrown, width/2, height - height/8, basketRadius);
                    basket[1] = make_unique<Rect>(grassGreen, width/2, height - height/8 - basketRadius/2, base);
                    break;
            }
            if (key == 32) {
                screen = play;
            }
            break;
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:
            switch(screen) {
                case play:
                    for (unique_ptr<Shape> &b : basket) {
                        b->move(-3,0);
                    }
            }
            break;
        case GLUT_KEY_RIGHT:
            switch(screen) {
                case play:
                    for (unique_ptr<Shape> &b : basket) {
                        b->move(3,0);
                    }
            }
            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}

void appleTimer(int index) {
    bool state1 = apples[index].getBottomY() >= basket[1]->getBottomY();
    bool state2 = apples[index].getRightX() <= basket[0]->getRightX() && apples[index].getLeftX() >= basket[0]->getLeftX();
    switch(screen) {
        case play:
            apples[index].moveY(apples[index].getRadius());
            if (state2 && state1) {
                apples.erase(apples.begin() + index);
                score++;
            }
            if (apples[index].getBottomY() >= height) {
                index++;
            }
            if (index == apples.size()) {
                screen = final;
            }
            break;
    }
    glutPostRedisplay();
    glutTimerFunc(30, appleTimer, index);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(450, 0); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Newton's Apple" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, appleTimer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
