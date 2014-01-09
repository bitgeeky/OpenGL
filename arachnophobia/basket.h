#ifndef BASKET_H_
#define BASKET_H_

class Basket {

    public:

        float w;
        float cx, cy;
        Basket(float x, float y, float width){

            cx = x;
            cy = y;
            w = width;
        }

        void draw(){
            float x = cx, y = cy;
              glBegin(GL_QUADS);
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

