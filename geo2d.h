#ifndef GEO2D
#define GEO2D
#include<iostream>
#include<vector>
#include<cmath>
#define CLSystem LCSystem
#define LPSystem PLSystem
#define CPSystem PCSystem
#define LINESEG_BEGINNING 0
#define LINESEG_ENDING 1
#define TRIANGLE_FIRSTPOINT 0
#define TRIANGLE_SECONDPOINT 1
#define TRIANGLE_THIRDPOINT 2
#define _USE_MATH_DEFINES
using namespace std;
class Line;
class Circle;
constexpr double pi(){return M_PI;}
class Point{
    public:
        Point(double x,double y):x(x),y(y),exist(true){}
        Point(bool e):x(0),y(0),exist(e){}
        Point(const Point&oth)=default;
        Point&operator=(const Point&oth)=default;
        ~Point()=default;
        double x;
        double y;
        bool exist;
        void rotate(Point c,double rad);
        void reflect(const Line&l);
        friend ostream&operator<<(ostream&os,const Point&p);
};
class Line{
    public:
        Line(double A,double B,double C):A(A),B(B),C(C),exist(true){}
        Line(bool e):A(0),B(0),C(0),exist(e){}
        Line(const Line&oth)=default;
        Line&operator=(const Line&oth)=default;
        ~Line()=default;
        double A;
        double B;
        double C;
        bool exist;
        void rotate(Point c,double rad);
        void reflect(Line l);
        friend ostream&operator<<(ostream&os,const Line&l);
};
class Circle{
    public:
        Circle(Point c,double r):c(c),r(r),exist(true){}
        Circle(bool e):c(Point(e)),r(0),exist(e){}
        Circle(const Circle&oth)=default;
        Circle&operator=(const Circle&oth)=default;
        ~Circle()=default;
        Point c;
        double r;
        bool exist;
        friend ostream&operator<<(ostream&os,const Circle&c);
};
class nPoints{
    public:
        nPoints(int n,vector<Point>pList):n(n),pList(pList){}
        nPoints(const nPoints&oth)=default;
        nPoints&operator=(const nPoints&oth)=default;
        ~nPoints()=default;
        int n;
        vector<Point>pList;
        void rotate(Point c,double rad);
};
class LineSeg:public nPoints{
    public:
        LineSeg(Point p1,Point p2):nPoints(2,vector<Point>()){
            pList.push_back(p1);
            pList.push_back(p2);
        }
        LineSeg(const LineSeg&oth)=default;
        LineSeg&operator=(const LineSeg&oth)=default;
        ~LineSeg()=default;
        Line lineExpr();
        Point midpoint();
        Line perpendicularBisector();
        double length();
        Point getPoint(int i,double dist);
        friend ostream&operator<<(ostream&os,const LineSeg&l);
};
class Angle:public nPoints{
    public:
        Angle(Point p1,Point p2,Point p3):nPoints(3,vector<Point>()){
            pList.push_back(p1);
            pList.push_back(p2);
            pList.push_back(p3);
        }
        Angle(const Angle&oth)=default;
        Angle&operator=(const Angle&oth)=default;
        ~Angle()=default;
        double measure();
        Line angleBisector();
        Line supplementaryAngleBisector();
        friend ostream&operator<<(ostream&os,const Angle&a);
};
class Triangle:public nPoints{
    public:
        Triangle(Point p1,Point p2,Point p3):nPoints(3,vector<Point>()){
            pList.push_back(p1);
            pList.push_back(p2);
            pList.push_back(p3);
        }
        Triangle(const Triangle&oth)=default;
        Triangle&operator=(const Triangle&oth)=default;
        ~Triangle()=default;
        Point incenter();
        Point circumcenter();
        Circle excircle(int fp,int sp);
        Triangle anticevianTriangle();
        friend ostream&operator<<(ostream&os,const Triangle&t);
};
class PLSystem{
    public:
        PLSystem(Point p,Line l):p(p),l(l){}
        PLSystem(Line l,Point p):p(p),l(l){}
        PLSystem(const PLSystem&oth)=default;
        PLSystem&operator=(const PLSystem&oth)=default;
        ~PLSystem()=default;
        Point p;
        Line l;
        double distance();
        Point orthogonalPoint();
        Line perpendicularLine();
        Line parallalLine();
};
class LLSystem{
    public:
        LLSystem(Line l1,Line l2):l1(l1),l2(l2){}
        LLSystem(const LLSystem&oth)=default;
        LLSystem&operator=(const LLSystem&oth)=default;
        ~LLSystem()=default;
        Line l1;
        Line l2;
        Point intersectionPoint();
        double distance();
};
class LCSystem{
    public:
        LCSystem(Line l,Circle c):l(l),c(c){}
        LCSystem(Circle c,Line l):l(l),c(c){}
        LCSystem(const LCSystem&oth)=default;
        LCSystem&operator=(const LCSystem&oth)=default;
        ~LCSystem()=default;
        Line l;
        Circle c;
        double distance();
        vector<Point>intersectionPoints();
};
class PCSystem{
    public:
        PCSystem(Point p,Circle c):p(p),c(c){}
        PCSystem(Circle c,Point p):p(p),c(c){}
        PCSystem(const PCSystem&oth)=default;
        PCSystem&operator=(const PCSystem&oth)=default;
        ~PCSystem()=default;
        Point p;
        Circle c;
        Line tangentLine();
};
class CCSystem{
    public:
        CCSystem(Circle c1,Circle c2):c1(c1),c2(c2){}
        CCSystem(const CCSystem&oth)=default;
        CCSystem&operator=(const CCSystem&oth)=default;
        ~CCSystem()=default;
        Circle c1;
        Circle c2;
        double distance();
        vector<Point>intersectionPoints();
};
#undef _USE_MATH_DEFINES
#endif

