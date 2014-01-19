/*
    Pop out laser beams and the spiders from 
    array.
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include "cannon.h"
#include "basket.h"
#include "spider.h"
#include "laser.h"
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void drawScene();
void addspider(int value);
void movespiders(int value);
void movebeams(int value);
void reflectbeams(int value);
void drawBox(float len);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

// Global Variables
float box_len = 4.0f;
Cannon tank(0.0f,0.0f,0.15f); //Make a Cannon type object 
Basket gr_basket(-0.5f,0.0f,0.2f,1); //Make a green basket
Basket red_basket(0.5f,0.0f,0.2f,0); //Make a red basket
vector<Spider> arr;
vector<Laser> beam;
//Laser beam(0.0f, 0.0f, 3.0f, 0.0f);
float tank_velx = 0.04f; 
float tank_vely = 0.0f;
float basket_velx = 0.04f; 
float basket_vely = 0.5f;
int move_object = 0;
float theta = 0.0f;
float ball_vel = 0.02f;
int num = 0;
int beamctr = 0;
int main(int argc, char **argv) {

    srand (time(NULL));
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
    glutTimerFunc(50, movespiders, 0);
    glutTimerFunc(2000, addspider, 0);
    glutTimerFunc(10, movebeams, 0);
    glutTimerFunc(10, reflectbeams, 0);

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

    //Draw beam
    if(beamctr>0){
        int i=0;
        for(i=0;i<beamctr;i++){
    glPushMatrix();
    glTranslatef(beam[i].gettankx(), beam[i].gettanky(), 0.0f);
    //glTranslatef(beam[i].getx(), -1.8f, 0.0f);
    glRotatef(beam[i].getangle(), 0.0f, 0.0f, 1.0f);
    beam[i].draw();
    glPopMatrix();
        }
    }

    //Draw green basket
    glPushMatrix();
    glTranslatef(gr_basket.getx(), -1.8f, 0.0f);
    gr_basket.draw();
    glPopMatrix();

    //Draw red basket
    glPushMatrix();
    glTranslatef(red_basket.getx(), -1.8f, 0.0f);
    red_basket.draw();
    glPopMatrix();

     //Draw Ball
     if(num>0){
     int i=0;
     for(i=0;i<num;i++){
     glPushMatrix();
     glTranslatef(arr[i].getx(), arr[i].gety(), 0.0f);
     arr[i].draw();
     glPopMatrix();
     }
     }

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
void movespiders(int value) {
    if(num>0){
        int i=0;
    for(i=0;i<num;i+=1){
        if(arr[i].clr == 1){
            // red spider coming 
            if((arr[i].gety()<=(-1.8+red_basket.w))&&(arr[i].gety()>=(-1.8))){                    if((arr[i].getx()<=(red_basket.getx()+red_basket.w))&&(arr[i].getx()>=(red_basket.getx()-red_basket.w))){
                    arr.erase (arr.begin()+i);
                    i-=1;
                    num-=1;
                    }
            }
        }
        else if(arr[i].clr == 2){
            // green spider coming

        }
        if(arr[i].gety()>(-1.8)){
        arr[i].update(0.0f,-ball_vel);
        }
    }
    }
    glutTimerFunc(50, movespiders, 0);
     
}

void movebeams(int value) {
    if(beamctr>0){
        int i=0;
    for(i=0;i<beamctr;i++){
        beam[i].update();
    }
    }
    glutTimerFunc(10, movebeams, 0);
     
}

void reflectbeams(int value) {
    if(beamctr>0){
        int i=0;
    for(i=0;i<beamctr;i++){
        
           if(beam[i].gettankx()>0){
                if(box_len/2 - beam[i].gettankx()+ beam[i].velx < 0.4f){
                    beam[i].theta *= -1;
                    beam[i].tankx -= 0.1f;
                }
           }
            
           if(beam[i].gettankx()<0){
                if(abs(box_len/2) - abs(beam[i].gettankx()+ beam[i].velx) < 0.4f){
                    beam[i].theta *= -1;
                    beam[i].tankx += 0.1f;
                }
           }
    }
    }
    glutTimerFunc(10, reflectbeams, 0);
     
}

void addspider(int value) {
    int clr = rand() % 3 + 1; //generate random color
    //generate random x co-ordinate
    float ix = rand() % 17 + 1;
    float fx = ix/10;//convert to float and smaller value
    int flag = rand() % 2 + 1;
    if(flag == 1)
        fx *= -1;

    num+=1;

    arr.push_back(Spider (fx,1.9f,0.1f,clr));
    glutTimerFunc(2000, addspider, 0);
}
void addbeam(){
    
    beamctr += 1;
    beam.push_back(Laser(0.0f,0.0f,4.0f,theta,tank.getx(), -1.8f));
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
    if(key == 32)
        addbeam();
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
            theta += 20;
        else if (button == GLUT_RIGHT_BUTTON)
            theta -= 20;
    }

}
