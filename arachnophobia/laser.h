#ifndef LASER_H_
#define LASER_H_
#define DEG2RAD(deg) (deg * PI / 180)
#include <math.h>
class Laser {

    public:

        float w;
        float cx, cy;
        float theta;
        Laser(float x, float y, float width, float t){

            cx = x;
            cy = y;
            w = width;
            theta = t;
        }

        void draw(){

            glLineWidth(w); 
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex3f(cx, cy, 0.0);
            glVertex3f(cx, cy+0.4f, 0);
            glEnd();

        }

        void update(float x, float y, float t){
            cx += x;
            cy += y;
            theta = t;
        }

        float getx(){ return cx;}
        float gety(){ return cy;}
        float getangle(){ return theta;}
};

#endif

