#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "cannon.h"
#include "basket.h"
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

// Global Variables
float box_len = 4.0f;
Cannon tank(0.0f,0.0f,0.15f); //Make a Cannon type object 
Basket gr_basket(-0.5f,-0.9f,0.2f,1); //Make a green basket
Basket red_basket(0.5f,-0.9f,0.2f,0); //Make a red basket
float tank_velx = 0.01f; 
float tank_vely = 0.0f;
float basket_velx = 0.02f; 
float basket_vely = 0.0f;
int move_object = 0;
float theta = 0.0f;

int main(int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("Arachnophobia");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}

// Function to draw objects on the screen
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    //Draw Box
    glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBox(box_len);

    //Draw Cannon in Centre 
    glPushMatrix();

    glTranslatef(tank.getx(), -1.8f, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    tank.draw();
    glPopMatrix();

    //Draw green basket
    glPushMatrix();
    glTranslatef(gr_basket.getx(), -0.9f, 0.0f);
    gr_basket.draw();
    glPopMatrix();

    //Draw red basket
    glPushMatrix();
    glTranslatef(red_basket.getx(), red_basket.gety(), 0.0f);
    red_basket.draw();
    glPopMatrix();

    //Draw a fixed Planck
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.0f);
    glVertex3f(2.0f, -1.92f, 0.0f);
    glVertex3f(-2.0f, -1.92f, 0.0f);
    glVertex3f(-2.0f, -2.0f, 0.0f);
    glVertex3f(2.0f, -2.0f, 0.0f);
    glEnd();
    glPopMatrix();


    glPopMatrix();
    glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
    glutTimerFunc(10, update, 0);
}

void drawBox(float len) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
    if(key == 'r')
        move_object = 2;
    if(key == 'g') 
        move_object = 1;
    if(key == 'b') 
        move_object = 3;
}

void handleKeypress2(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT){
        if(move_object==3)
            tank.update(-tank_velx,tank_vely);
        else if(move_object==1)
            gr_basket.update(-basket_velx, basket_vely);
        else if(move_object==2)
            red_basket.update(-basket_velx,basket_vely);
    }
    if (key == GLUT_KEY_RIGHT){
        if(move_object==3)
            tank.update(tank_velx,tank_vely);
        else if(move_object==1)
            gr_basket.update(basket_velx, basket_vely);
        else if(move_object==2)
            red_basket.update(basket_velx,basket_vely);
    }
}

void handleMouseclick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            theta += 15;
        else if (button == GLUT_RIGHT_BUTTON)
            theta -= 15;
    }

}
