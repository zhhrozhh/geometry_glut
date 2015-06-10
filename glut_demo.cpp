#define WINDOWWIDTH 500
#define WINDOWHEIGHT 500
#include"geo2d_glut.h"
#include"func_glut.h"
void disp(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    Point pa(-3.33,-9.4);
    Point pb(3.77,-2.244);
    Point pc(1.33,8.15);
    Triangle t(pa,pb,pc);
    /*glColor3f(1,0,0);
    drawTriangle(t);
    glColor3f(0,1,0);
    drawLine(Angle(pa,pb,pc).supplementaryAngleBisector());
    drawLine(Angle(pb,pa,pc).supplementaryAngleBisector());
    drawLine(Angle(pa,pc,pb).supplementaryAngleBisector());
    glColor3f(0,0,1);
    drawLine(Angle(pa,pb,pc).angleBisector());
    drawLine(Angle(pb,pa,pc).angleBisector());
    drawLine(Angle(pa,pc,pb).angleBisector());*/
    drawTriangle(t.anticevianTriangle());
    for(int i=0;i<40;i++){
        glColor3f(0,0.2,double(i+10)/50);
        drawTriangle(t);
        t = t.anticevianTriangle();
    }
    //drawFunction(new Sin(new X),100,10.0);
    //drawFunction(new Mul(new X(),new X()),100,true);
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

