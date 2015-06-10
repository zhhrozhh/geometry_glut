#ifndef FUNCGLUT
#define FUNCGLUT
#include<GLUT/GLUT.h>
#include"RealFunction.h"

#ifndef WINDOWWIDTH
#define WINDOWWIDTH 1000.0
#endif

#ifndef WINDOWHEIGHT
#define WINDOWHEIGHT 1000.0
#endif

class RGBAcolor{
    public:
        RGBAcolor(double r,double g,double b,double a):r(r),g(g),b(b),a(a){}
        double r;
        double g;
        double b;
        double a;
};
class RGBcolor:public RGBAcolor{
    public:
        RGBcolor(double r,double g,double b):RGBAcolor(r,g,b,1){}
};
void drawFunction(RFunction*f,int samples,double radius){
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<2*samples;i++){
        glVertex2d(-1.0+(double)i/(double)samples,f->value(-radius+(double)i*(radius)/(double)samples));
    }
    glEnd();
}
void drawFunction(RFunction*f,int samples,double radius,vector<RGBAcolor>colorList){
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<2*samples;i++){
        RGBAcolor c = colorList[i%colorList.size()];
        glColor3f(c.r,c.g,c.b);
        glVertex2d(-1.0+(double)i/(double)samples,f->value(-radius+(double)i*(radius)/(double)samples));
    }
    glEnd();
}
void drawFunction(RFunction*f,int samples,bool color){
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<2*samples;i++){
        double y = f->value(-(WINDOWWIDTH/2.0)+(double)i*(WINDOWWIDTH/2.0)/(double)samples) / WINDOWHEIGHT;
        if(color)glColor3f(0,0.3,abs(y));
        glVertex2d(-1.0+(double)i/(double)samples,y);
    }
    glEnd();
}

#endif


