#ifndef LASER_H_
#define LASER_H_
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#include <math.h>
#include <cmath>
class Laser {

    public:

        float w;
        float cx, cy;
        float theta;
        float tankx;
        float tanky;
        int istrans;
        float velx, vely;
        Laser(float x, float y, float width, float t, float tx, float ty){

            cx = x;
            cy = y;
            w = width;
            theta = t;
            tanky = ty;
            tankx = tx;
            istrans = 0;
            velx = 0.03f;
            vely = 0.03f;
        }

        void draw(){

            glLineWidth(w); 
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex3f(cx, cy, 0.0);
            glVertex3f(cx, cy+0.5f, 0);
            glEnd();

        }

        void update(){
            istrans = 1;
            if(theta<0){
                tankx += velx;
                tanky += -velx/tan(3.14*(theta/180));
            }
            else if(theta == 0){
                tanky += vely;
            }
            else{
                tankx -= velx;
                tanky += velx/tan(3.14*(theta/180));
            }
        }

        float getx(){ return cx;}
        float gety(){ return cy;}
        float getangle(){ return theta;}
        float gettankx(){ return tankx;}
        float gettanky(){ return tanky;}
};

#endif

