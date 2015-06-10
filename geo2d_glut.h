#ifndef GEO2D_GLUT
#define GEO2D_GLUT
#include<GLUT/GLUT.h>
#include"geo2d.h"
#ifndef WINDOWWIDTH
#define WINDOWWIDTH 1000.0
#endif
#ifndef WINDOWHEIGHT
#define WINDOWHEIGHT 1000.0
#endif

void drawTriangle(Triangle t){
    glBegin(GL_LINE_LOOP);
    glVertex2d(t.pList[0].x/(WINDOWWIDTH/2),t.pList[0].y/(WINDOWHEIGHT/2));
    glVertex2d(t.pList[1].x/(WINDOWWIDTH/2),t.pList[1].y/(WINDOWHEIGHT/2));
    glVertex2d(t.pList[2].x/(WINDOWWIDTH/2),t.pList[2].y/(WINDOWHEIGHT/2));
    glEnd();
}
void drawLineSeg(LineSeg ls){
    glBegin(GL_LINE_STRIP);
    glVertex2d(ls.pList[0].x/(WINDOWWIDTH/2),ls.pList[0].y/(WINDOWHEIGHT/2));
    glVertex2d(ls.pList[1].x/(WINDOWWIDTH/2),ls.pList[1].y/(WINDOWHEIGHT/2));
    glEnd();
}
void drawLine(Line l){
    if(l.B==0){
        glBegin(GL_LINE_STRIP);
        glVertex2d((-l.C/l.A)/(WINDOWWIDTH/2),1);
        glVertex2d((-l.C/l.A)/(WINDOWWIDTH/2),-1);
        glEnd();
    }else{
        glBegin(GL_LINE_STRIP);
        glVertex2d(-1.0,(((WINDOWWIDTH/2)*l.A-l.C)/l.B)/(WINDOWHEIGHT/2));
        glVertex2d(1.0,((-(WINDOWWIDTH/2)*l.A-l.C)/l.B)/(WINDOWHEIGHT/2));
        glEnd();
    }
}
void drawCircle(Circle c){
    double x0 = c.c.x+c.r;
    double y0 = c.c.y;
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<3600;i++)
        glVertex2d((x0+c.r*cos((double)i*2*pi()/3600))/(WINDOWWIDTH/2),(y0+c.r*sin((double)i*2*pi()/3600))/(WINDOWHEIGHT/2));
    glEnd();
}

#endif





