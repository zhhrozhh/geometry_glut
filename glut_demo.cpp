#define WINDOWWIDTH 500
#define WINDOWHEIGHT 500
#include"geo2d_glut.h"
#include"func_glut.h"
void disp(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    Point pa(-30.33,-15.4);
    Point pb(30.77,-17.244);
    Point pc(0.33,50.15);
    Triangle t(pa,pb,pc);

    Circle cc0 = t.excircle(TRIANGLE_FIRSTPOINT,TRIANGLE_SECONDPOINT);
    Circle cc1 = t.excircle(TRIANGLE_THIRDPOINT,TRIANGLE_SECONDPOINT);
    Circle cc2 = t.excircle(TRIANGLE_FIRSTPOINT,TRIANGLE_THIRDPOINT);

    drawCircle(cc0);
    drawCircle(cc1);
    drawCircle(cc2);

    glColor3f(0,1,0);
    drawLine(Angle(pa,pb,pc).supplementaryAngleBisector());
    drawLine(Angle(pb,pa,pc).supplementaryAngleBisector());
    drawLine(Angle(pa,pc,pb).supplementaryAngleBisector());
    glColor3f(0.3,0.1,0.8);
    drawLine(LineSeg(pa,pb).lineExpr());
    drawLine(LineSeg(pa,pc).lineExpr());
    drawLine(LineSeg(pb,pc).lineExpr());
    glColor3f(1,0,0);
    RFunction*f = new Mul(new ConstantFunction(100),new Cos(new Mul(new ConstantFunction(5), new X())));
    RFunction*g = f->d();

    glColor3f(0.33,0.6,0.33);
    drawFunction(f,100,false);
    glColor3f(0.12,0.6,0.14);
    drawFunction(g,100,false);
    glColor3f(1,0,0);
    drawTriangle(t);
    
    drawCircle(Circle(Point(0,0),0.4));
    glutSwapBuffers();
}
int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("demo");
    glutDisplayFunc(disp);
    glutMainLoop();
}

