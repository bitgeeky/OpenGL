#ifndef SPIDER_H_
#define SPIDER_H_

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

class Spider {

    public:

        float w;
        float cx, cy;
        float rad;
        int clr;
        int flag;
        Spider(float x, float y, float radius, int c){

            cx = x;
            cy = y;
            rad = radius;
            clr = c;
            flag = 0;
        }

        void draw(){

            if(clr == 1)
                glColor3f(0.1f, 0.0f, 0.0f);
            else if(clr == 2)
                glColor3f(0.0f, 1.0f, 0.0f);
            else if(clr == 3)
                glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_FAN);
            for(int i=0 ; i<360 ; i++) {
                glVertex2f((rad-0.06f) * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
            }
            glEnd();
        }

        void update(float x, float y){
            cx += x;
            cy += y;
        }

        float getx(){ return cx;}
        float gety(){ return cy;}
};

#endif

