#ifndef BASKET_H_
#define BASKET_H_

class Basket {

    public:

        float w;
        float cx, cy;
        int clr;
        Basket(float x, float y, float width,int c){

            cx = x;
            cy = y;
            w = width;
            clr = c;
        }

        void draw(){
            float x = cx, y = cy;
              glBegin(GL_QUADS);
                if(clr)
                glColor3f(0.0f, 0.1f, 0.0f); 
                else
                glColor3f(0.1f, 0.0f, 0.0f); 
                glVertex3f(x+w, y+w, 0.0f); 
                glVertex3f(x-w, y+w, 0.0f); 
                glVertex3f(x-w, y-w, 0.0f); 
                glVertex3f(x+w, y-w, 0.0f); 
                glEnd();/* 
            glBegin(GL_QUADS);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5f, 0.5f, 0.0f);
            glVertex3f(-0.5f, 0.5f, 0.0f);
            glVertex3f(-0.5f, -0.5f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.0f);
            glEnd();*/
        }

        void update(float x, float y){
            cx += x;
            cy += y;
        }

        float getx(){ return cx;}
        float gety(){ return cy;}
};

#endif

