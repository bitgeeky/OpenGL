#ifndef LASER_H_
#define LASER_H_
#define DEG2RAD(deg) (deg * PI / 180)
#include <math.h>
class Laser {

    public:

        float w;
        float cx, cy;
        float theta;
        float tankx;
        float tanky;
        int istrans;
        Laser(float x, float y, float width, float t, float tx, float ty){

            cx = x;
            cy = y;
            w = width;
            theta = t;
            tanky = ty;
            tankx = tx;
            istrans = 0;
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
            istrans = 1;
            if(theta>0)
                cx += x;
            else
                cx -= x;
            cy += y;
            theta = t;
        }

        float getx(){ return cx;}
        float gety(){ return cy;}
        float getangle(){ return theta;}
        float gettankx(){ return tankx;}
        float gettanky(){ return tanky;}
};

#endif

