#include"geo2d.h"

int main(){
    Point a(1,0);
    Point b(0,1);
    LineSeg ls(a,b);
    Line l = ls.lineExpr();
    cout<<"line "<<l<<" pass through "<<a<<" and "<<b<<endl;
    
    cout<<"perpendicular bisector of "<<ls<<" is "<<ls.perpendicularBisector()<<endl;


    l = Line(3.15,0.33,-2.3);
    Line l1(2.34,-2.1,0.99);
    LLSystem lls(l,l1);
    cout<<"the intersection point of line "<<l<<" and "<<l1<<" is "<<lls.intersectionPoint()<<endl;
    Point c(0,0);
    Angle ang(a,c,b);
    cout<<ang<<" is "<<ang.measure()<<" radius"<<endl;
    cout<<"angle bisector of "<<ang<<" is "<<ang.angleBisector()<<endl;
    Triangle t(a,b,c);
    cout<<t<<endl;
    cout<<"<====================="<<endl;
    cout<<"<====================="<<endl;
    Point pa(133,-34.1);
    Point pb(44.66,12.69);
    Point pc(72,9.77);
    Angle angl(pa,pb,pc);
    cout<<angl.angleBisector()<<endl;
    cout<<"<====================="<<endl;
    cout<<"<====================="<<endl;
}
